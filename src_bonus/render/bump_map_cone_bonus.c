/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_cone_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:03:54 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 11:04:26 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static void	compute_bump_uv_and_tangents_cone(t_bump_data *b, t_cone *cone,
		t_vec3 hit_point, double bump_scale)
{
	t_vec3	rel;
	double	height_on_axis;
	t_vec3	radial;
	double	base_radius;
	double	radius_at_height;
	t_vec3	axis_dir;

	axis_dir = cone->direction;
	// 円錐頂点からのベクトル
	rel = vec_sub(hit_point, cone->apex);
	// 軸方向の高さ成分
	height_on_axis = vec_dot(rel, axis_dir);
	// 円錐の底面半径を計算
	base_radius = tan(cone->angle) * cone->height;
	// 指定高さでの半径
	radius_at_height = (height_on_axis / cone->height) * base_radius;
	// 軸方向成分を引いて放射方向ベクトル取得
	radial = vec_sub(rel, vec_mul(axis_dir, height_on_axis));
	// 接線ベクトルの計算（円筒版と似た方法）
	if (fabs(axis_dir.y) > 0.99)
		b->tangent = (t_vec3){1, 0, 0};
	else
		b->tangent = vec_normalize(vec_cross((t_vec3){0, 1, 0}, axis_dir));
	b->bitangent = vec_cross(axis_dir, b->tangent);
	// UV計算
	// uは角度方向 (atan2)、vは高さ方向スケール
	if (vec_len2(radial) < 1e-6)
		radial = b->tangent;
	else
		radial = vec_normalize(radial);
	b->u = atan2(radial.z, radial.x) * bump_scale;
	b->v = height_on_axis * bump_scale;
}

t_vec3	apply_bump_map_cone(t_hit_record *rec, t_cone *cone)
{
	t_bump_data	b;
	t_vec3		normal;
	double		bump_scale;
	double		bump_strength;

	bump_scale = 20.0;
	bump_strength = 0.3;
	normal = rec->normal;
	if (fabs(vec_dot(normal, cone->direction)) > 0.99)
		return (normal); // 頂点付近などではバンプマップ不適用（適宜変更可能）
	compute_bump_uv_and_tangents_cone(&b, cone, rec->hit_point, bump_scale);
	b.bump = sin(b.u) + 0.5 * sin(2 * b.u + b.v) + 0.25 * cos(3 * b.v + b.u);
	b.perturb = vec_add(vec_mul(b.tangent, sin(b.u)), vec_mul(b.bitangent,
				cos(b.v)));
	if (vec_len2(b.perturb) < 1e-6)
		b.perturb = (t_vec3){0, 0, 0};
	else
		b.perturb = vec_mul(b.perturb, b.bump * bump_strength);
	return (vec_normalize(vec_add(normal, b.perturb)));
}
