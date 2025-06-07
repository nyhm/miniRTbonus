/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:56:32 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 20:11:55 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

t_color	color_mul(t_color a, t_color b)
{
	return ((t_color){a.r * b.r, a.g * b.g, a.b * b.b});
}

t_color	color_scale(t_color color, double scale)
{
	return ((t_color){color.r * scale, color.g * scale, color.b * scale});
}

void	find_closest_intersection(t_data *data, t_hit_record *record)
{
	find_closest_plane(data, record);
	find_closest_sphere(data, record);
	find_closest_cylinder(data, record);
}
