/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:46:38 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/02 17:03:19 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

// 球とレイの交差判定
int hit_sphere(t_sphere *s, t_ray ray, double *t_hit)
{
    t_vec3 oc = vec_sub(ray.origin, s->center);
    double a = vec_dot(ray.direction, ray.direction);
    double b = 2.0 * vec_dot(oc, ray.direction);
    double c = vec_dot(oc, oc) - s->radius * s->radius;
    double discriminant = b*b - 4*a*c;

    if (discriminant < 0)
        return 0;
    double t1 = (-b - sqrt(discriminant)) / (2*a);
    double t2 = (-b + sqrt(discriminant)) / (2*a);
    if (t1 > 0.001) {
        *t_hit = t1;
        return 1;
    }
    if (t2 > 0.001) {
        *t_hit = t2;
        return 1;
    }
    return 0;
}

int hit_plane(t_plane *pl, t_ray ray, double *t_hit)
{
    double denom = vec_dot(pl->normal, ray.direction);
    if (fabs(denom) > 1e-6) { // 平行でない場合
        double t = vec_dot(vec_sub(pl->point, ray.origin), pl->normal) / denom;
        if (t >= 0.001) {
            *t_hit = t;
            return 1;
        }
    }
    return 0;
}

int hit_cylinder(t_cylinder *cy, t_ray ray, double *t_hit)
{
    // シリンダーの軸方向（単位ベクトル）
    t_vec3 ca = cy->direction;
    // レイの始点からシリンダー底面中心へのベクトル
    t_vec3 oc = vec_sub(ray.origin, cy->center);

    // ray.direction と oc を軸方向から射影（軸に平行な成分を除く）
    t_vec3 dir_proj = vec_sub(ray.direction, vec_mul(ca, vec_dot(ray.direction, ca)));
    t_vec3 oc_proj = vec_sub(oc, vec_mul(ca, vec_dot(oc, ca)));

    double a = vec_dot(dir_proj, dir_proj);
    double b = 2.0 * vec_dot(dir_proj, oc_proj);
    double c = vec_dot(oc_proj, oc_proj) - cy->radius * cy->radius;

    double discriminant = b * b - 4 * a * c;
    double t_candidates[4];
    int count = 0;

    if (discriminant >= 0 && a > 1e-12) {
        double sqrt_disc = sqrt(discriminant);
        double t0 = (-b - sqrt_disc) / (2 * a);
        double t1 = (-b + sqrt_disc) / (2 * a);

        // 側面交点の高さ制限を確認
        int i;
        i=0;
        while(i < 2) {
            double t_side;
            if (i == 0)
                t_side = t0;
            else
                t_side = t1;
            if (t_side > 0.001) {
                t_vec3 p = vec_add(ray.origin, vec_mul(ray.direction, t_side));
                double height_proj = vec_dot(vec_sub(p, cy->center), ca);
                if (height_proj >= 0 && height_proj <= cy->height) {
                    t_candidates[count++] = t_side;
                }
            }
            i++;
        }
    }

    // 底面との交点判定
    t_vec3 n = ca; // 法線は軸方向
    t_vec3 p0 = cy->center; // 底面の中心点
    double denom = vec_dot(n, ray.direction);
    if (fabs(denom) > 1e-6) {
        double t_plane = vec_dot(vec_sub(p0, ray.origin), n) / denom;
        if (t_plane > 0.001) {
            t_vec3 p = vec_add(ray.origin, vec_mul(ray.direction, t_plane));
            t_vec3 v = vec_sub(p, p0);
            // 軸方向成分を除く距離を計算（底面の半径以内か）
            double dist = vec_len2(vec_sub(v, vec_mul(n, vec_dot(v, n))));
            if (dist <= cy->radius*cy->radius) {
                t_candidates[count++] = t_plane;
            }
        }
    }

    // 上面との交点判定
    t_vec3 p1 = vec_add(cy->center, vec_mul(ca, cy->height)); // 上面の中心点
    denom = vec_dot(n, ray.direction);
    if (fabs(denom) > 1e-6) {
        double t_plane = vec_dot(vec_sub(p1, ray.origin), n) / denom;
        if (t_plane > 0.001) {
            t_vec3 p = vec_add(ray.origin, vec_mul(ray.direction, t_plane));
            t_vec3 v = vec_sub(p, p1);
            double dist = vec_len2(vec_sub(v, vec_mul(n, vec_dot(v, n))));
            if (dist <= cy->radius*cy->radius) {
                t_candidates[count++] = t_plane;
            }
        }
    }

    // 最も近い交点を選択
    if (count == 0)
        return 0;

    double t_min = 1e30;
    int i = 0;
    while( i < count) {
        if (t_candidates[i] < t_min && t_candidates[i] > 0.001)
            t_min = t_candidates[i];
        i++;
    }

    if (t_min == 1e30)
        return 0;

    *t_hit = t_min;
    return 1;
}
