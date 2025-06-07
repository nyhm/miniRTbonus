/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:46:34 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 16:01:53 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

t_color	opposite_color(t_color c);
t_color	get_checkerboard_color(t_hit_record *record, t_plane *pl, double scale);
t_color	get_sphere_checker_color(t_hit_record *record, t_sphere *s,
			double scale);

t_color	opposite_color(t_color c)
{
	t_color	opp;

	opp.r = 255 - c.r;
	opp.g = 255 - c.g;
	opp.b = 255 - c.b;
	return (opp);
}

t_color	get_checkerboard_color(t_hit_record *record, t_plane *pl, double scale)
{
	t_vec3	relative;
	t_vec3	u;
	t_vec3	v;
	double	u_coord;
	double	v_coord;

	if (fabs(record->normal.y) < 0.99)
		u = vec_cross(record->normal, (t_vec3){0, 1, 0});
	else
		u = vec_cross(record->normal, (t_vec3){1, 0, 0});
	u = vec_normalize(u);
	v = vec_cross(record->normal, u);
	relative = vec_sub(record->hit_point, pl->point);
	u_coord = vec_dot(relative, u) * scale;
	v_coord = vec_dot(relative, v) * scale;
	if (((int)floor(u_coord) + (int)floor(v_coord)) % 2 == 0)
		return (record->color);
	else
		return (opposite_color(record->color));
}

t_color	get_sphere_checker_color(t_hit_record *record, t_sphere *s,
		double scale)
{
	t_vec3	p_centered;
	double	theta;
	double	phi;

	p_centered = vec_sub(record->hit_point, s->center);
	theta = atan2(p_centered.z, p_centered.x);
	if (theta < 0)
		theta += 2 * M_PI;
	phi = acos(p_centered.y / s->radius);
	if (((int)(theta * scale) + (int)(phi * scale)) % 2 == 0)
		return (record->color);
	else
		return (opposite_color(s->color));
}
