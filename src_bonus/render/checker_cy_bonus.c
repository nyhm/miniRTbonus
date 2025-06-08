/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_cy_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:05:30 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 09:53:01 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static int	is_cylinder_checkerboard(t_vec3 point, t_cylinder *cy);
// t_color		get_cylinder_checker_color(t_vec3 point, t_cylinder *cy);

static int	is_cylinder_cap_checkerboard(t_vec3 point, t_cylinder *cy,
		double scale, int is_top)
{
	t_cy_cap_checkerboard_vars	vars;

	if (is_top)
		vars.center = vec_add(cy->center, vec_mul(cy->direction, cy->height
					* 0.5));
	else
		vars.center = vec_sub(cy->center, vec_mul(cy->direction, cy->height
					* 0.5));
	vars.diff = vec_sub(point, vars.center);
	vars.up = (t_vec3){0, 1, 0};
	if (fabs(vec_dot(cy->direction, vars.up)) > 0.999)
		vars.up = (t_vec3){1, 0, 0};
	vars.u = vec_normalize(vec_cross(vars.up, cy->direction));
	vars.v = vec_normalize(vec_cross(cy->direction, vars.u));
	vars.x_2d = vec_dot(vars.diff, vars.u) * scale;
	vars.y_2d = vec_dot(vars.diff, vars.v) * scale;
	vars.checker = ((int)floor(vars.x_2d) + (int)floor(vars.y_2d)) % 2;
	if (vars.checker < 0)
		vars.checker += 2;
	return (vars.checker == 0);
}

static int	is_cylinder_checkerboard(t_vec3 point, t_cylinder *cy)
{
	t_cy_checkerboard_vars	vars;
	t_cy_checkerboard_scale	scale;

	scale = (t_cy_checkerboard_scale){1.0, 10.0, 1.0};
	vars.cp = vec_sub(point, cy->center);
	vars.height = vec_dot(vars.cp, cy->direction);
	vars.half_height = cy->height * 0.5;
	if (vars.height < -vars.half_height + 0.001)
		return (is_cylinder_cap_checkerboard(point, cy, scale.bottom, 0));
	else if (vars.height > vars.half_height - 0.001)
		return (is_cylinder_cap_checkerboard(point, cy, scale.bottom, 1));
	else
	{
		vars.radial = vec_sub(vars.cp, vec_mul(cy->direction, vars.height));
		vars.angle = atan2(vars.radial.z, vars.radial.x) * scale.angle;
		vars.h = (vars.height + vars.half_height) * scale.height;
		vars.checker = ((int)floor(vars.angle) + (int)floor(vars.h)) % 2;
		if (vars.checker < 0)
			vars.checker += 2;
		return (vars.checker == 0);
	}
}

t_color	get_cylinder_checker_color(t_vec3 point, t_cylinder *cy)
{
	if (is_cylinder_checkerboard(point, cy))
		return (cy->color);
	else
		return (opposite_color(cy->color));
}
