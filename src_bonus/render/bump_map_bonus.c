/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:52:04 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 16:03:02 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

t_vec3		apply_bump_map(t_hit_record *rec);
t_vec3		apply_bump_map_sphere(t_hit_record *rec);
static void	compute_bump_uv_and_tangents(t_bump_data *b, t_cylinder *cy, \
										t_vec3 hit_point, double bump_scale);
t_vec3		apply_bump_map_cylinder(t_hit_record *rec, t_cylinder *cy);

t_vec3	apply_bump_map(t_hit_record *rec)
{
	t_bump_data	b;
	t_vec3		new_normal;
	double		bump_scale;
	double		bump_strength;

	bump_scale = 20.0;
	bump_strength = 0.2;
	if (fabs(rec->normal.y) > 0.99)
		b.tangent = vec_normalize(vec_cross((t_vec3){0, 0, 1}, rec->normal));
	else
		b.tangent = vec_normalize(vec_cross((t_vec3){0, 1, 0}, rec->normal));
	b.bitangent = vec_cross(rec->normal, b.tangent);
	b.u = vec_dot(rec->hit_point, b.tangent) * bump_scale;
	b.v = vec_dot(rec->hit_point, b.bitangent) * bump_scale;
	b.bump = 0.5 * sin(b.u) + 0.25 * sin(2 * b.u + b.v) + \
			0.125 * cos(3 * b.v + b.u) + 0.0625 * sin(5 * b.u + 4 * b.v);
	b.perturb = vec_add(vec_mul(b.tangent, sin(b.u)), \
			vec_mul(b.bitangent, cos(b.v)));
	b.perturb = vec_mul(b.perturb, b.bump * bump_strength);
	new_normal = vec_normalize(vec_add(rec->normal, b.perturb));
	return (new_normal);
}

t_vec3	apply_bump_map_sphere(t_hit_record *rec)
{
	t_bump_data	b;
	t_vec3		normal;
	double		bump_scale;
	double		bump_strength;

	normal = rec->normal;
	bump_scale = 20.0;
	bump_strength = 0.2;
	if (fabs(normal.x) > 0.9)
		b.tangent = vec_normalize(vec_cross((t_vec3){0, 1, 0}, normal));
	else
		b.tangent = vec_normalize(vec_cross((t_vec3){1, 0, 0}, normal));
	b.bitangent = vec_cross(normal, b.tangent);
	b.u = atan2(normal.z, normal.x) * bump_scale;
	b.v = acos(normal.y) * bump_scale;
	b.bump = sin(b.u) + 0.5 * sin(2 * b.u + b.v) + 0.25 * cos(3 * b.v + b.u);
	b.perturb = vec_add(vec_mul(b.tangent, sin(b.u)), vec_mul(b.bitangent, \
				cos(b.v)));
	b.perturb = vec_mul(b.perturb, b.bump * bump_strength);
	b.new_normal = vec_normalize(vec_add(normal, b.perturb));
	return (b.new_normal);
}

static void	compute_bump_uv_and_tangents(t_bump_data *b, t_cylinder *cy, \
		t_vec3 hit_point, double bump_scale)
{
	t_vec3	rel;
	t_vec3	rel_proj;

	if (fabs(cy->direction.y) > 0.99)
		b->tangent = (t_vec3){1, 0, 0};
	else
		b->tangent = vec_normalize(vec_cross((t_vec3){0, 1, 0}, cy->direction));
	b->bitangent = vec_cross(cy->direction, b->tangent);
	rel = vec_sub(hit_point, cy->center);
	b->v = vec_dot(rel, cy->direction);
	rel_proj = vec_sub(rel, vec_mul(cy->direction, b->v));
	if (vec_len2(rel_proj) < 1e-6)
		rel_proj = b->tangent;
	else
		rel_proj = vec_normalize(rel_proj);
	b->u = atan2(rel_proj.z, rel_proj.x) * bump_scale;
	b->v *= bump_scale;
}

t_vec3	apply_bump_map_cylinder(t_hit_record *rec, t_cylinder *cy)
{
	t_bump_data	b;
	t_vec3		normal;
	double		bump_scale;
	double		bump_strength;

	normal = rec->normal;
	bump_scale = 20.0;
	bump_strength = 0.3;
	if (fabs(vec_dot(normal, cy->direction)) > 0.99)
		return (apply_bump_map(rec));
	compute_bump_uv_and_tangents(&b, cy, rec->hit_point, bump_scale);
	b.bump = sin(b.u) + 0.5 * sin(2 * b.u + b.v) + 0.25 * cos(3 * b.v + b.u);
	b.perturb = vec_add(vec_mul(b.tangent, sin(b.u)), vec_mul(b.bitangent, \
				cos(b.v)));
	if (vec_len2(b.perturb) < 1e-6)
		b.perturb = (t_vec3){0, 0, 0};
	else
		b.perturb = vec_mul(b.perturb, b.bump * bump_strength);
	return (vec_normalize(vec_add(normal, b.perturb)));
}
