/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:45:50 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/06 22:44:30 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

t_vec3	vec_rotate(t_vec3 v, t_vec3 r, double theta);
t_vec3	vec_reflect(t_vec3 I, t_vec3 N);
t_vec3	parse_vec3(const char *str);
t_vec3	vec_normalize(t_vec3 v);

t_vec3	vec_rotate(t_vec3 v, t_vec3 r, double theta)
{
	double	cos_t;
	double	sin_t;
	double	dot;
	t_vec3	cross;

	cos_t = cos(theta);
	sin_t = sin(theta);
	dot = vec_dot(r, v);
	cross = vec_cross(r, v);
	return ((t_vec3){v.x * cos_t + cross.x * sin_t + r.x * dot * (1 - cos_t),
		v.y * cos_t + cross.y * sin_t + r.y * dot * (1 - cos_t), v.z * cos_t
		+ cross.z * sin_t + r.z * dot * (1 - cos_t)});
}

t_vec3	vec_reflect(t_vec3 I, t_vec3 N)
{
	return (vec_sub(I, vec_mul(N, 2.0 * vec_dot(I, N))));
}

t_vec3	parse_vec3(const char *str)
{
	t_vec3	vec;
	char	**parts;

	parts = ft_split(str, ',');
	if (!parts || ft_count_words(str, ',') != 3)
		return ((t_vec3){0, 0, 0});
	vec.x = ft_atof(parts[0]);
	vec.y = ft_atof(parts[1]);
	vec.z = ft_atof(parts[2]);
	free_split(parts);
	return (vec);
}

t_vec3	vec_normalize(t_vec3 v)
{
	t_vec3	result;
	double	length;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length == 0.0)
		return ((t_vec3){0, 0, 0});
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;
	return (result);
}
