/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_cone_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:03:54 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 16:01:54 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static void	compute_bump_uv_and_tangents_cone(t_bump_data *b, t_cone *cone, \
	t_vec3 hit_point, double bump_scale);
t_vec3		apply_bump_map_cone(t_hit_record *rec, t_cone *cone);

static void	compute_bump_uv_and_tangents_cone(t_bump_data *b, t_cone *cone, \
		t_vec3 hit_point, double bump_scale)
{
	t_cone_bump_vars	vars;

	vars.axis_dir = cone->direction;
	vars.rel = vec_sub(hit_point, cone->apex);
	vars.height_on_axis = vec_dot(vars.rel, vars.axis_dir);
	vars.base_radius = tan(cone->angle) * cone->height;
	vars.radius_at_height = (vars.height_on_axis / cone->height) \
		* vars.base_radius;
	vars.radial = vec_sub(vars.rel, vec_mul(vars.axis_dir, \
				vars.height_on_axis));
	if (fabs(vars.axis_dir.y) > 0.99)
		b->tangent = (t_vec3){1, 0, 0};
	else
		b->tangent = vec_normalize(vec_cross((t_vec3){0, 1, 0}, vars.axis_dir));
	b->bitangent = vec_cross(vars.axis_dir, b->tangent);
	if (vec_len2(vars.radial) < 1e-6)
		vars.radial = b->tangent;
	else
		vars.radial = vec_normalize(vars.radial);
	b->u = atan2(vars.radial.z, vars.radial.x) * bump_scale;
	b->v = vars.height_on_axis * bump_scale;
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
		return (normal);
	compute_bump_uv_and_tangents_cone(&b, cone, rec->hit_point, bump_scale);
	b.bump = sin(b.u) + 0.5 * sin(2 * b.u + b.v) + 0.25 * cos(3 * b.v + b.u);
	b.perturb = vec_add(vec_mul(b.tangent, sin(b.u)), vec_mul(b.bitangent, \
				cos(b.v)));
	if (vec_len2(b.perturb) < 1e-6)
		b.perturb = (t_vec3){0, 0, 0};
	else
		b.perturb = vec_mul(b.perturb, b.bump * bump_strength);
	return (vec_normalize(vec_add(normal, b.perturb)));
}
