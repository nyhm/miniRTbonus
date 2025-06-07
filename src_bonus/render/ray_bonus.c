/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:46:25 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 19:11:09 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

//t_ray				create_ray(t_vec3 origin, t_vec3 direction);
static t_hit_record	hit_record_init(t_ray ray);
// t_color				trace_ray(t_ray ray, t_data *data);
// t_ray				generate_camera_ray(t_data *data, t_coord coord);

t_ray	create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

static t_hit_record	hit_record_init(t_ray ray)
{
	t_hit_record	rec;

	rec.ray = ray;
	rec.t = INFINITY;
	rec.sphere_index = -1;
	rec.plane_index = -1;
	rec.cylinder_index = -1;
	rec.normal = (t_vec3){0, 0, 0};
	rec.hit_point = (t_vec3){0, 0, 0};
	rec.color = (t_color){0, 0, 0};
	return (rec);
}

t_color	trace_ray(t_ray ray, t_data *data)
{
	int				i;
	t_color			final;
	t_hit_record	record;
	t_light			light;
	t_color			light_result;

	final = (t_color){0, 0, 0};
	record = hit_record_init(ray);
	find_closest_intersection(data, &record);
	if (record.t < INFINITY && data->scene->light_count)
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
	dir = vec_normalize(vec_add(vec_add(vec_mul(data->scene->camera.right, \
						coord.px), vec_mul(data->scene->camera.up, coord.py)), \
				data->scene->camera.dir));
	return (create_ray(data->scene->camera.pos, dir));
}
