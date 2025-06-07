/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 07:38:38 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 12:53:26 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static void	find_closest_plane(t_data *data, t_hit_record *record);
static void	find_closest_sphere(t_data *data, t_hit_record *record);
static void	set_cylinder(t_hit_record *record, double t_hit, t_data *data,
				int i);
static void	find_closest_cylinder(t_data *data, t_hit_record *record);
void		find_closest_intersection(t_data *data, t_hit_record *record);

int	is_checkerboard_z(t_vec3 point, double scale)
{
	int	y;
	int	x;

	y = (int)floor(point.y * scale);
	x = (int)floor(point.x * scale);
	return ((y + x) % 2 == 0);
}

t_color	get_checkerboard_color_z(t_vec3 point, double scale, t_color c1,
		t_color c2)
{
	if (is_checkerboard_z(point, scale))
		return (c1);
	else
		return (c2);
}

int	is_checkerboard_x(t_vec3 point, double scale)
{
	int	y;
	int	z;

	y = (int)floor(point.y * scale);
	z = (int)floor(point.z * scale);
	return ((y + z) % 2 == 0);
}

t_color	get_checkerboard_color_x(t_vec3 point, double scale, t_color c1,
		t_color c2)
{
	if (is_checkerboard_x(point, scale))
		return (c1);
	else
		return (c2);
}

int	is_checkerboard_y(t_vec3 point, double scale)
{
	int	x;
	int	z;

	x = (int)floor(point.x * scale);
	z = (int)floor(point.z * scale);
	return ((x + z) % 2 == 0);
}

t_color	get_checkerboard_color_y(t_vec3 point, double scale, t_color c1,
		t_color c2)
{
	if (is_checkerboard_y(point, scale))
		return (c1);
	else
		return (c2);
}

t_color	opposite_color(t_color c)
{
	t_color	opp;

	opp.r = 255 - c.r;
	opp.g = 255 - c.g;
	opp.b = 255 - c.b;
	return (opp);
}

int	is_cylinder_bottom_checkerboard(t_vec3 point, t_cylinder *cy, double scale)
{
	t_vec3	axis;
	t_vec3	bottom_center;
	t_vec3	diff;
	t_vec3	world_up;
	t_vec3	u;
	t_vec3	v;
	double	x_2d;
	double	y_2d;
	int		checker_x;
	int		checker_y;

	axis = cy->direction;
	bottom_center = cy->center;
	diff = vec_sub(point, bottom_center);
	world_up = (t_vec3){0, 1, 0};
	u = vec_normalize(vec_cross(axis, world_up));
	if (vec_len2(u) < 0.001)
		u = (t_vec3){1, 0, 0};
	v = vec_cross(axis, u);
	x_2d = vec_dot(diff, u) * scale;
	y_2d = vec_dot(diff, v) * scale;
	checker_x = (int)floor(x_2d);
	checker_y = (int)floor(y_2d);
	return ((checker_x + checker_y) % 2 == 0);
}

int	is_cylinder_checkerboard(t_vec3 point, t_cylinder *cy, double scale_height,
		double scale_angle, double scale_bottom)
{
	t_vec3	axis;
	t_vec3	cp;
	double	height;
	double	scaled_height;
	t_vec3	radial;
	double	angle;
	int		checker_x;
	int		checker_y;

	axis = cy->direction;
	cp = vec_sub(point, cy->center);
	height = vec_dot(cp, axis);
	if (height < 0.001)
		return (is_cylinder_bottom_checkerboard(point, cy, scale_bottom));
	else
	{
		scaled_height = height * scale_height;
		radial = vec_sub(cp, vec_mul(axis, height));
		angle = atan2(radial.z, radial.x) * scale_angle;
		checker_x = (int)floor(scaled_height);
		checker_y = (int)floor(angle);
		return ((checker_x + checker_y) % 2 == 0);
	}
}

t_color	get_cylinder_checker_color(t_vec3 point, t_cylinder *cy,
		double scale_height, double scale_angle, double scale_bottom,
		t_color c1, t_color c2)
{
	if (is_cylinder_checkerboard(point, cy, scale_height, scale_angle,
			scale_bottom))
		return (c1);
	else
		return (c2);
}

static void	find_closest_plane(t_data *data, t_hit_record *record)
{
	double	t_hit;
	int		i;
	t_plane	*pl;
	t_color	alt;

	i = 0;
	while (i < data->scene->plane_count)
	{
		t_hit = 0.0;
		if (hit_plane(&data->scene->planes[i], record->ray, &t_hit)
			&& t_hit < record->t && t_hit > 0.001)
		{
			pl = &data->scene->planes[i];
			record->plane_index = i;
			record->normal = pl->normal;
			record->t = t_hit;
			record->sphere_index = -1;
			record->cylinder_index = -1;
			record->hit_point = vec_add(record->ray.origin,
					vec_mul(record->ray.direction, t_hit));
			record->color = pl->color;
			alt = opposite_color(record->color);
			if (pl->normal.y != 0 && pl->checkerboard)
				record->color = get_checkerboard_color_y(record->hit_point, 0.5,
						record->color, alt);
			else if (pl->normal.x != 0 && pl->checkerboard)
				record->color = get_checkerboard_color_x(record->hit_point, 0.5,
						record->color, alt);
			else if (pl->normal.z != 0 && pl->checkerboard)
				record->color = get_checkerboard_color_z(record->hit_point, 0.5,
						record->color, alt);
		}
		i++;
	}
}

t_color	get_sphere_checker_color(t_vec3 point, t_vec3 center, double radius,
		double scale, t_color c1, t_color c2)
{
	t_vec3	p_centered;
	double	theta;
	double	phi;
	int		check_u;
	int		check_v;

	p_centered = vec_sub(point, center);
	theta = atan2(p_centered.z, p_centered.x);
	if (theta < 0)
		theta += 2 * M_PI;
	phi = acos(p_centered.y / radius);
	check_u = (int)(theta * scale);
	check_v = (int)(phi * scale);
	if ((check_u + check_v) % 2 == 0)
		return (c1);
	else
		return (c2);
}

static void	find_closest_sphere(t_data *data, t_hit_record *record)
{
	int			i;
	double		t_hit;
	t_sphere	*s;

	i = 0;
	while (i < data->scene->sphere_count)
	{
		t_hit = 0.0;
		if (hit_sphere(&data->scene->spheres[i], record->ray, &t_hit)
			&& t_hit < record->t && t_hit > 0.001)
		{
			s = &data->scene->spheres[i];
			record->t = t_hit;
			record->color = s->color;
			record->sphere_index = i;
			record->plane_index = -1;
			record->cylinder_index = -1;
			record->hit_point = vec_add(record->ray.origin,
					vec_mul(record->ray.direction, t_hit));
			record->normal = vec_normalize(vec_sub(record->hit_point,
						s->center));
			record->hit_point = record->hit_point;
			if (s->checkerboard)
				record->color = get_sphere_checker_color(record->hit_point,
						s->center, s->radius, 3.0, s->color,
						opposite_color(s->color));
		}
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
	record->hit_point = vec_add(record->ray.origin,
			vec_mul(record->ray.direction, t_hit));
	cp = vec_sub(record->hit_point, cy->center);
	proj = vec_dot(cp, cy->direction);
	record->normal = vec_normalize(vec_sub(cp, vec_mul(cy->direction, proj)));
	if (cy->checkerboard)
		record->color = get_cylinder_checker_color(record->hit_point, cy, 1.0,
				10.0, 1.0, cy->color, opposite_color(cy->color));
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
