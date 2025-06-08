/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_cone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:01:11 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 11:10:11 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

typedef struct s_cone_checkerboard_vars
{
	t_vec3 vec; // apexからのベクトル
	double	height_on_axis;
	double	base_radius;
	double	radius_at_height;
	t_vec3	radial;
	double	dist;
	double	angle_2d;
	double	height_scaled;
	int		checker;
}			t_cone_checkerboard_vars;

static int	is_cone_checkerboard(t_vec3 point, t_cone *cone, double scale)
{
	t_cone_checkerboard_vars	vars;

	vars.vec = vec_sub(point, cone->apex);
	vars.height_on_axis = vec_dot(vars.vec, cone->direction);
	if (vars.height_on_axis < 0 || vars.height_on_axis > cone->height)
		return (0); // 円錐の高さ外
	vars.base_radius = tan(cone->angle) * cone->height;
	vars.radius_at_height = (vars.height_on_axis / cone->height)
		* vars.base_radius;
	vars.radial = vec_sub(vars.vec, vec_mul(cone->direction,
				vars.height_on_axis));
	vars.dist = vec_len2(vars.radial);
	if (vars.dist > vars.radius_at_height * vars.radius_at_height)
		return (0); // 円錐の外
	vars.angle_2d = atan2(vars.radial.z, vars.radial.x) * scale;
	vars.height_scaled = vars.height_on_axis * scale;
	vars.checker = ((int)floor(vars.angle_2d) + (int)floor(vars.height_scaled))
		% 2;
	if (vars.checker < 0)
		vars.checker += 2;
	return (vars.checker == 0);
}

t_color	get_cone_checker_color(t_vec3 point, t_cone *cone)
{
	const double	scale = 10.0;

	if (is_cone_checkerboard(point, cone, scale))
		return (cone->color);
	else
		return (opposite_color(cone->color));
}
