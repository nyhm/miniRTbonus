/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:46:25 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 12:23:15 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

t_ray	create_ray(t_vec3 origin, t_vec3 direction);
t_ray	generate_camera_ray(t_data *data, t_coord coord);
t_color	trace_ray(t_ray ray, t_data *data);

t_ray	create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_color	trace_ray(t_ray ray, t_data *data)
{
	int				i;
	t_color			final;
	t_hit_record	record;
	t_light			light;
	t_color			light_result;

	final = (t_color){0, 0, 0};
	record = (t_hit_record){ray, INFINITY, -1, -1, -1, {0, 0, 0}, {0, 0, 0}, \
		{100, 100, 100}};
	find_closest_intersection(data, &record);
	if (record.t < INFINITY)
	{
		i = 0;
		while (i < data->scene->light_count)
		{
			light = data->scene->lights[i];
			light_result = apply_lighting(record, light, data);
			light_set(&final, light_result);
			i++;
		}
	}
	else
		final = record.color;
	return (final);
}

t_ray	generate_camera_ray(t_data *data, t_coord coord)
{
	t_vec3	dir;
	double	u;
	double	v;
	double	scale;

	u = (coord.x + (coord.sx + 0.5) / SAMPLES) / WIDTH;
	v = (coord.y + (coord.sy + 0.5) / SAMPLES) / HEIGHT;
	scale = tan(data->scene->camera.fov * 0.5 * M_PI / 180.0);
	coord.px = (2 * u - 1) * data->scene->camera.aspect_ratio * scale;
	coord.py = (1 - 2 * v) * scale;
	dir = vec_normalize(vec_add(vec_add(vec_mul(data->scene->camera.right,
						coord.px), vec_mul(data->scene->camera.up, coord.py)),
				data->scene->camera.dir));
	return (create_ray(data->scene->camera.pos, dir));
}
