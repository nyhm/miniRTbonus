/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:27:12 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/06 22:44:27 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

t_vec3	vec3(double x, double y, double z);
double	vec_len2(t_vec3 v);
t_vec3	vec_scale(t_vec3 v, double s);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);

t_vec3	vec3(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

double	vec_len2(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3	vec_scale(t_vec3 v, double s)
{
	t_vec3	result;

	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;
	return (result);
}

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}
