/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_cy_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:05:30 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 07:53:41 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static int	is_cylinder_bottom_checkerboard(t_vec3 point, t_cylinder *cy, \
				double scale);
static int	is_cylinder_checkerboard(t_vec3 point, t_cylinder *cy);
//t_color		get_cylinder_checker_color(t_vec3 point, t_cylinder *cy);

static int	is_cylinder_bottom_checkerboard(t_vec3 point, t_cylinder *cy, \
		double scale)
{
	t_vec3	bottom_center;
	t_vec3	diff;
	t_vec3	u;
	double	x_2d;
	double	y_2d;

	bottom_center = cy->center;
	diff = vec_sub(point, bottom_center);
	u = vec_normalize(vec_cross(cy->direction, (t_vec3){0, 1, 0}));
	if (vec_len2(u) < 0.001)
		u = (t_vec3){1, 0, 0};
	x_2d = vec_dot(diff, u) * scale;
	y_2d = vec_dot(diff, vec_cross(cy->direction, u)) * scale;
	return (((int)floor(x_2d) + (int)floor(y_2d)) % 2 == 0);
}

static int	is_cylinder_checkerboard(t_vec3 point, t_cylinder *cy)
{
	t_cy_checkerboard_scale	scale;
	t_cy_coord				coord;
	t_vec3					cp;
	double					height;
	t_vec3					radial;

	scale = (t_cy_checkerboard_scale){1.0, 10.0, 1.0};
	cp = vec_sub(point, cy->center);
	height = vec_dot(cp, cy->direction);
	if (height < 0.001)
		return (is_cylinder_bottom_checkerboard(point, cy, scale.bottom));
	else
	{
		coord.height = height * scale.height;
		radial = vec_sub(cp, vec_mul(cy->direction, height));
		coord.angle = atan2(radial.z, radial.x) * scale.angle;
		return (((int)floor(coord.height) + (int)floor(coord.angle)) % 2 == 0);
	}
}

t_color	get_cylinder_checker_color(t_vec3 point, t_cylinder *cy)
{
	if (is_cylinder_checkerboard(point, cy))
		return (cy->color);
	else
		return (opposite_color(cy->color));
}
