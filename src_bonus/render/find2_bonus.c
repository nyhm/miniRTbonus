/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:57:12 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 11:57:06 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static void	set_plane(t_hit_record *record, double t_hit, t_data *data, int i)
{
	t_plane	*pl;

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
	if (pl->bump_map)
		record->normal = apply_bump_map(record);
}

void	find_closest_plane(t_data *data, t_hit_record *record)
{
	double	t_hit;
	int		i;

	i = 0;
	while (i < data->scene->plane_count)
	{
		t_hit = 0.0;
		if (hit_plane(&data->scene->planes[i], record->ray, &t_hit)
			&& t_hit < record->t && t_hit > 0.001)
			set_plane(record, t_hit, data, i);
		i++;
	}
}

static void	set_cone(t_hit_record *record, double t_hit, t_data *data, int i)
{
	t_cone	*cone;
	t_vec3	cp;
	double	proj;
	double	k;

	cone = &data->scene->cones[i];
	record->t = t_hit;
	record->color = cone->color;
	record->cone_index = i;
	record->sphere_index = -1;
	record->plane_index = -1;
	record->cylinder_index = -1;
	record->hit_point = vec_add(record->ray.origin, \
			vec_mul(record->ray.direction, t_hit));
	cp = vec_sub(record->hit_point, cone->apex);
	proj = vec_dot(cp, cone->direction);
	k = tan(cone->angle * 0.5 * M_PI / 180.0);
	record->normal = vec_normalize(vec_sub(cp, vec_mul(cone->direction, (1 + k
						* k) * proj)));
	if (cone->checkerboard)
		record->color = get_cone_checker_color(record->hit_point, cone);
	if (cone->bump_map)
		record->normal = apply_bump_map_cone(record, cone);
}

void	find_closest_cone(t_data *data, t_hit_record *record)
{
	int		i;
	double	t_hit;

	i = 0;
	while (i < data->scene->cone_count)
	{
		t_hit = 0.0;
		if (hit_cone(&data->scene->cones[i], record->ray, &t_hit)
			&& t_hit < record->t && t_hit > 0.001)
			set_cone(record, t_hit, data, i);
		i++;
	}
}
