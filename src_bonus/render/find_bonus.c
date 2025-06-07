/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 07:38:38 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 07:28:06 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

//void		find_closest_plane(t_data *data, t_hit_record *record);
static void	set_sphere(t_hit_record *record, double t_hit, t_data *data, int i);
//void		find_closest_sphere(t_data *data, t_hit_record *record);
static void	set_cylinder(t_hit_record *record, double t_hit, t_data *data, \
						int i);
//void		find_closest_cylinder(t_data *data, t_hit_record *record);

t_vec3 apply_bump_map(t_hit_record *rec)
{
	t_vec3	tangent, bitangent, perturb, new_normal;
	double	u, v, bump;
	double	bump_scale = 20.0;
	double	bump_strength = 0.2;

	// 法線と直交する接ベクトルを生成（特殊ケースも考慮）
	if (fabs(rec->normal.y) > 0.99)
		tangent = vec_normalize(vec_cross((t_vec3){0, 0, 1}, rec->normal));
	else
		tangent = vec_normalize(vec_cross((t_vec3){0, 1, 0}, rec->normal));
	bitangent = vec_cross(rec->normal, tangent);

	// ヒットポイントをローカル座標系（tangent/bitangent）に投影
	// これにより平面の方向に依存せずバンプが適用できる
	u = vec_dot(rec->hit_point, tangent) * bump_scale;
	v = vec_dot(rec->hit_point, bitangent) * bump_scale;

	// 複雑なバンプ関数（細かい模様）
	bump = 0.5 * sin(u);
	bump += 0.25 * sin(2 * u + v);
	bump += 0.125 * cos(3 * v + u);
	bump += 0.0625 * sin(5 * u + 4 * v);

	// 擾乱ベクトルを接ベクトル方向で計算
	perturb = vec_add(vec_mul(tangent, sin(u)), vec_mul(bitangent, cos(v)));
	perturb = vec_mul(perturb, bump * bump_strength);

	new_normal = vec_normalize(vec_add(rec->normal, perturb));
	return (new_normal);
}

t_vec3 apply_bump_map_sphere(t_hit_record *rec)
{
    t_vec3 normal = rec->normal; // 法線は既に計算済み（球の表面法線）
    t_vec3 tangent, bitangent, perturb, new_normal;
    double u, v;
    double bump_scale = 20.0;
    double bump_strength = 0.2;

    // 球の法線がそのまま中心からの方向ベクトルなので、
    // 接ベクトルを計算（球の法線に直交する任意のベクトルを選ぶ）
    if (fabs(normal.x) > 0.9)
        tangent = vec_normalize(vec_cross((t_vec3){0,1,0}, normal));
    else
        tangent = vec_normalize(vec_cross((t_vec3){1,0,0}, normal));
    bitangent = vec_cross(normal, tangent);

    // 球の表面の (u,v) 座標を計算（球面座標系）
    // u: 角度（経度） 0〜2π, v: 角度（緯度） 0〜π
    u = atan2(normal.z, normal.x) * bump_scale;
    v = acos(normal.y) * bump_scale;

    // バンプ関数（複雑にするなら複数のsin波などを重ねる）
    double bump = sin(u) + 0.5 * sin(2 * u + v) + 0.25 * cos(3 * v + u);

    // 擾乱ベクトルを計算
    perturb = vec_add(vec_mul(tangent, sin(u)), vec_mul(bitangent, cos(v)));
    perturb = vec_mul(perturb, bump * bump_strength);

    // 新しい法線を計算して正規化
    new_normal = vec_normalize(vec_add(normal, perturb));

    return new_normal;
}

t_vec3 apply_bump_map_cylinder(t_hit_record *rec, t_cylinder *cy)
{
	t_vec3 normal = rec->normal;
	t_vec3 tangent, bitangent, perturb, new_normal;
	t_vec3 rel, rel_proj;
	double u, v;
	double bump, bump_scale = 20.0, bump_strength = 0.3;

	// キャップ面（上下の平面）なら、平面バンプ処理に切り替える
	if (fabs(vec_dot(normal, cy->direction)) > 0.99)
	{


		new_normal = apply_bump_map(rec);
		return new_normal;
	}

	// ----------- 側面処理（以前の処理） -----------
	if (fabs(cy->direction.y) > 0.99)
		tangent = (t_vec3){1, 0, 0};
	else
		tangent = vec_normalize(vec_cross((t_vec3){0, 1, 0}, cy->direction));
	bitangent = vec_cross(cy->direction, tangent);

	rel = vec_sub(rec->hit_point, cy->center);
	v = vec_dot(rel, cy->direction);
	rel_proj = vec_sub(rel, vec_mul(cy->direction, v));
	if (vec_len2(rel_proj) < 1e-6)
		rel_proj = tangent;
	else
		rel_proj = vec_normalize(rel_proj);
	u = atan2(rel_proj.z, rel_proj.x);

	u *= bump_scale;
	v *= bump_scale;
	bump = sin(u) + 0.5 * sin(2 * u + v) + 0.25 * cos(3 * v + u);

	perturb = vec_add(vec_mul(tangent, sin(u)), vec_mul(bitangent, cos(v)));
	if (vec_len2(perturb) < 1e-6)
		perturb = (t_vec3){0, 0, 0};
	else
		perturb = vec_mul(perturb, bump * bump_strength);

	new_normal = vec_normalize(vec_add(normal, perturb));
	return new_normal;
}




void	find_closest_plane(t_data *data, t_hit_record *record)
{
	double	t_hit;
	int		i;
	t_plane	*pl;

	i = 0;
	while (i < data->scene->plane_count)
	{
		t_hit = 0.0;
		if (hit_plane(&data->scene->planes[i], record->ray, &t_hit) \
				&& t_hit < record->t && t_hit > 0.001)
		{
			pl = &data->scene->planes[i];
			record->plane_index = i;
			record->normal = pl->normal;
			record->t = t_hit;
			record->sphere_index = -1;
			record->cylinder_index = -1;
			record->hit_point = vec_add(record->ray.origin, \
									vec_mul(record->ray.direction, t_hit));
			record->color = pl->color;
			if (pl->checkerboard)
				record->color = get_checkerboard_color(record, pl, 0.5);
			record->normal = apply_bump_map(record);
		}
		i++;
	}
}

static void	set_sphere(t_hit_record *record, double t_hit, t_data *data, int i)
{
	t_sphere	*s;

	s = &data->scene->spheres[i];
	record->t = t_hit;
	record->color = s->color;
	record->sphere_index = i;
	record->plane_index = -1;
	record->cylinder_index = -1;
	record->hit_point = vec_add(record->ray.origin, \
							vec_mul(record->ray.direction, t_hit));
	record->normal = vec_normalize(vec_sub(record->hit_point, s->center));
	record->hit_point = record->hit_point;
	if (s->checkerboard)
		record->color = get_sphere_checker_color(record, s, 3.0);
	record->normal = apply_bump_map_sphere(record);
}

void	find_closest_sphere(t_data *data, t_hit_record *record)
{
	int		i;
	double	t_hit;

	i = 0;
	while (i < data->scene->sphere_count)
	{
		t_hit = 0.0;
		if (hit_sphere(&data->scene->spheres[i], record->ray, &t_hit) \
				&& t_hit < record->t && t_hit > 0.001)
			set_sphere(record, t_hit, data, i);
		i++;
	}
}

static void	set_cylinder(t_hit_record *record, double t_hit, t_data *data,
		int i)
{
	t_cylinder	*cy;
	t_vec3		cp;
	double		proj;

	cy = &data->scene->cylinders[i];
	record->t = t_hit;
	record->color = cy->color;
	record->cylinder_index = i;
	record->sphere_index = -1;
	record->plane_index = -1;
	record->hit_point = vec_add(record->ray.origin, \
							vec_mul(record->ray.direction, t_hit));
	cp = vec_sub(record->hit_point, cy->center);
	proj = vec_dot(cp, cy->direction);
	record->normal = vec_normalize(vec_sub(cp, vec_mul(cy->direction, proj)));
	if (cy->checkerboard)
		record->color = get_cylinder_checker_color(record->hit_point, cy);
	record->normal = apply_bump_map_cylinder(record,cy);
}

void	find_closest_cylinder(t_data *data, t_hit_record *record)
{
	int		i;
	double	t_hit;

	i = 0;
	while (i < data->scene->cylinder_count)
	{
		t_hit = 0.0;
		if (hit_cylinder(&data->scene->cylinders[i], record->ray, &t_hit) \
				&& t_hit < record->t && t_hit > 0.001)
			set_cylinder(record, t_hit, data, i);
		i++;
	}
}
