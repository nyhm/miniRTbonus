/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 07:38:38 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/06 08:00:02 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	find_closest_plane(t_data *data, t_hit_record *record);
static void	find_closest_sphere(t_data *data, t_hit_record *record);
static void	set_cylinder(t_hit_record *record, double t_hit, t_data *data,
				int i);
static void	find_closest_cylinder(t_data *data, t_hit_record *record);
void		find_closest_intersection(t_data *data, t_hit_record *record);

static void	find_closest_plane(t_data *data, t_hit_record *record)
{
	double	t_hit;
	int		i;

	i = 0;
	while (i < data->scene->plane_count)
	{
		t_hit = 0.0;
		if (hit_plane(&data->scene->planes[i], record->ray, &t_hit)
			&& t_hit < record->t && t_hit > 0.001)
		{
			record->plane_index = i;
			record->normal = data->scene->planes[i].normal;
			record->t = t_hit;
			record->sphere_index = -1;
			record->cylinder_index = -1;
			record->hit_point = vec_add(record->ray.origin,
					vec_mul(record->ray.direction, t_hit));
			record->color = data->scene->planes[i].color;
		}
		i++;
	}
}

static void	find_closest_sphere(t_data *data, t_hit_record *record)
{
	t_vec3	normal;
	int		i;
	double	t_hit;

	i = 0;
	while (i < data->scene->sphere_count)
	{
		t_hit = 0.0;
		if (hit_sphere(&data->scene->spheres[i], record->ray, &t_hit)
			&& t_hit < record->t && t_hit > 0.001)
		{
			record->t = t_hit;
			record->color = data->scene->spheres[i].color;
			record->sphere_index = i;
			record->plane_index = -1;
			record->cylinder_index = -1;
			record->hit_point = vec_add(record->ray.origin,
					vec_mul(record->ray.direction, t_hit));
			normal = vec_normalize(vec_sub(record->hit_point,
						data->scene->spheres[i].center));
			record->normal = normal;
		}
		i++;
	}
}

static void	set_cylinder(t_hit_record *record, double t_hit, t_data *data,
		int i)
{
	t_vec3	cp;
	double	proj;

	record->t = t_hit;
	record->color = data->scene->cylinders[i].color;
	record->cylinder_index = i;
	record->sphere_index = -1;
	record->plane_index = -1;
	record->hit_point = vec_add(record->ray.origin,
			vec_mul(record->ray.direction, t_hit));
	cp = vec_sub(record->hit_point, data->scene->cylinders[i].center);
	proj = vec_dot(cp, data->scene->cylinders[i].direction);
	record->normal = vec_normalize(vec_sub(cp,
				vec_mul(data->scene->cylinders[i].direction, proj)));
}

static void	find_closest_cylinder(t_data *data, t_hit_record *record)
{
	int		i;
	double	t_hit;

	i = 0;
	while (i < data->scene->cylinder_count)
	{
		t_hit = 0.0;
		if (hit_cylinder(&data->scene->cylinders[i], record->ray, &t_hit)
			&& t_hit < record->t && t_hit > 0.001)
			set_cylinder(record, t_hit, data, i);
		i++;
	}
}

void	find_closest_intersection(t_data *data, t_hit_record *record)
{
	find_closest_plane(data, record);
	find_closest_sphere(data, record);
	find_closest_cylinder(data, record);
}
