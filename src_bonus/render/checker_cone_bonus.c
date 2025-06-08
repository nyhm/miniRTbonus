/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_cone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:01:11 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 12:27:51 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static int	is_cone_checkerboard(t_vec3 point, t_cone *cone, double scale)
{
	t_cone_checkerboard_vars	vars;
	t_vec3						up;
	t_vec3						u;
	t_vec3						v;

	vars.vec = vec_sub(point, cone->apex);
	vars.height_on_axis = vec_dot(vars.vec, cone->direction);
	if (vars.height_on_axis < 0 || vars.height_on_axis > cone->height)
		return (0);
	up = (t_vec3){0, 1, 0};
	if (fabs(vec_dot(cone->direction, up)) > 0.999)
		up = (t_vec3){1, 0, 0};
	u = vec_normalize(vec_cross(up, cone->direction));
	v = vec_normalize(vec_cross(cone->direction, u));
	vars.radial = vec_sub(vars.vec, vec_mul(cone->direction,
				vars.height_on_axis));
	vars.u_coord = vec_dot(vars.radial, u) * scale;
	vars.v_coord = vec_dot(vars.radial, v) * scale;
	vars.checker = ((int)floor(vars.u_coord) + (int)floor(vars.v_coord)) % 2;
	if (vars.checker < 0)
		vars.checker += 2;
	return (vars.checker == 0);
}

t_color	get_cone_checker_color(t_vec3 point, t_cone *cone)
{
	const double	scale = 3.0;

	if (is_cone_checkerboard(point, cone, scale))
		return (cone->color);
	else
		return (opposite_color(cone->color));
}
