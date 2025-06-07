/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 07:38:38 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 19:13:01 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

//void		find_closest_plane(t_data *data, t_hit_record *record);
static void	set_sphere(t_hit_record *record, double t_hit, t_data *data, int i);
//void		find_closest_sphere(t_data *data, t_hit_record *record);
static void	set_cylinder(t_hit_record *record, double t_hit, t_data *data, \
						int i);
//void		find_closest_cylinder(t_data *data, t_hit_record *record);

void	find_closest_plane(t_data *data, t_hit_record *record)
{
	double	t_hit;
	int		i;
	t_plane	*pl;

	i = 0;
	while (i < data->scene->plane_count)
	{
		t_hit = 0.0;
		if (hit_plane(&data->scene->planes[i], record->ray, &t_hit) \
				&& t_hit < record->t && t_hit > 0.001)
		{
			pl = &data->scene->planes[i];
			record->plane_index = i;
			record->normal = pl->normal;
			record->t = t_hit;
			record->sphere_index = -1;
			record->cylinder_index = -1;
			record->hit_point = vec_add(record->ray.origin, \
									vec_mul(record->ray.direction, t_hit));
			record->color = pl->color;
			if (pl->checkerboard)
				record->color = get_checkerboard_color(record, pl, 0.5);
		}
		i++;
	}
}

static void	set_sphere(t_hit_record *record, double t_hit, t_data *data, int i)
{
	t_sphere	*s;

	s = &data->scene->spheres[i];
	record->t = t_hit;
	record->color = s->color;
	record->sphere_index = i;
	record->plane_index = -1;
	record->cylinder_index = -1;
	record->hit_point = vec_add(record->ray.origin, \
							vec_mul(record->ray.direction, t_hit));
	record->normal = vec_normalize(vec_sub(record->hit_point, s->center));
	record->hit_point = record->hit_point;
	if (s->checkerboard)
		record->color = get_sphere_checker_color(record, s, 3.0);
}

void	find_closest_sphere(t_data *data, t_hit_record *record)
{
	int		i;
	double	t_hit;

	i = 0;
	while (i < data->scene->sphere_count)
	{
		t_hit = 0.0;
		if (hit_sphere(&data->scene->spheres[i], record->ray, &t_hit) \
				&& t_hit < record->t && t_hit > 0.001)
			set_sphere(record, t_hit, data, i);
		i++;
	}
}

static void	set_cylinder(t_hit_record *record, double t_hit, t_data *data,
		int i)
{
	t_cylinder	*cy;
	t_vec3		cp;
	double		proj;

	cy = &data->scene->cylinders[i];
	record->t = t_hit;
	record->color = cy->color;
	record->cylinder_index = i;
	record->sphere_index = -1;
	record->plane_index = -1;
	record->hit_point = vec_add(record->ray.origin, \
							vec_mul(record->ray.direction, t_hit));
	cp = vec_sub(record->hit_point, cy->center);
	proj = vec_dot(cp, cy->direction);
	record->normal = vec_normalize(vec_sub(cp, vec_mul(cy->direction, proj)));
	if (cy->checkerboard)
		record->color = get_cylinder_checker_color(record->hit_point, cy);
}

void	find_closest_cylinder(t_data *data, t_hit_record *record)
{
	int		i;
	double	t_hit;

	i = 0;
	while (i < data->scene->cylinder_count)
	{
		t_hit = 0.0;
		if (hit_cylinder(&data->scene->cylinders[i], record->ray, &t_hit) \
				&& t_hit < record->t && t_hit > 0.001)
			set_cylinder(record, t_hit, data, i);
		i++;
	}
}
