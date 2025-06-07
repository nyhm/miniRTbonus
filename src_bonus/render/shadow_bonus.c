/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 07:42:08 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 11:13:01 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

int	is_shadow_plane(t_vec3 point, t_light light, t_data *data, double t_hit);
int	is_shadow_sphere(t_vec3 point, t_light light, t_data *data, double t_hit);
int	is_shadow_cylinder(t_vec3 point, t_light light, t_data *data, double t_hit);
int	is_in_shadow(t_vec3 point, t_light light, t_data *data);

int	is_shadow_plane(t_vec3 point, t_light light, t_data *data, double t_hit)
{
	t_vec3	light_dir;
	double	light_distance;
	t_ray	shadow_ray;
	int		i;

	light_dir = vec_normalize(vec_sub(light.pos, point));
	light_distance = vec_len2(vec_sub(light.pos, point));
	shadow_ray = (t_ray){vec_add(point, vec_mul(light_dir, 1e-4)), light_dir};
	i = 0;
	while (i < data->scene->plane_count)
	{
		if (hit_plane(&data->scene->planes[i], shadow_ray, &t_hit)
			&& t_hit > 0.001 && t_hit * t_hit < light_distance)
			return (1);
		i++;
	}
	return (0);
}

int	is_shadow_sphere(t_vec3 point, t_light light, t_data *data, double t_hit)
{
	t_vec3	light_dir;
	double	light_distance;
	t_ray	shadow_ray;
	int		i;

	light_dir = vec_normalize(vec_sub(light.pos, point));
	light_distance = vec_len2(vec_sub(light.pos, point));
	shadow_ray = (t_ray){vec_add(point, vec_mul(light_dir, 1e-4)), light_dir};
	i = 0;
	while (i < data->scene->sphere_count)
	{
		if (hit_sphere(&data->scene->spheres[i], shadow_ray, &t_hit)
			&& t_hit > 0.001 && t_hit * t_hit < light_distance)
			return (1);
		i++;
	}
	return (0);
}

int	is_shadow_cylinder(t_vec3 point, t_light light, t_data *data, double t_hit)
{
	t_vec3	light_dir;
	double	light_distance;
	t_ray	shadow_ray;
	int		i;

	light_dir = vec_normalize(vec_sub(light.pos, point));
	light_distance = vec_len2(vec_sub(light.pos, point));
	shadow_ray = (t_ray){vec_add(point, vec_mul(light_dir, 1e-4)), light_dir};
	i = 0;
	while (i < data->scene->cylinder_count)
	{
		if (hit_cylinder(&data->scene->cylinders[i], shadow_ray, &t_hit)
			&& t_hit > 0.001 && t_hit * t_hit < light_distance)
			return (1);
		i++;
	}
	return (0);
}

int	is_in_shadow(t_vec3 point, t_light light, t_data *data)
{
	double	t_hit;
	int		shadowed;

	t_hit = 0.0;
	shadowed = is_shadow_plane(point, light, data, t_hit);
	shadowed |= is_shadow_sphere(point, light, data, t_hit);
	shadowed |= is_shadow_cylinder(point, light, data, t_hit);
	return (shadowed);
}
