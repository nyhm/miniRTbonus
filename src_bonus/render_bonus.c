/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:47:06 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/06 23:20:43 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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

void	put_pixel(t_data *data, int x, int y, t_color color)
{
	char	*dst;
	int		pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = (color.r << 16) | (color.g << 8) | (color.b);
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = pixel;
}

void	find_closest_plane(t_ray ray, t_data *data, t_color *color,
		t_hit_record *record)
{
	int		i;
	double	t_hit;
	t_plane	*pl;
	t_vec3	hit_point;
	t_color	base;
	t_color	alt;

	i = 0;
	while (i < data->scene->plane_count)
	{
		t_hit = 0.0;
		if (hit_plane(&data->scene->planes[i], ray, &t_hit) && t_hit < record->t
			&& t_hit > 0.001)
		{
			pl = &data->scene->planes[i];
			record->t = t_hit;
			record->plane_index = i;
			record->sphere_index = -1;
			record->cylinder_index = -1;
			hit_point = vec_add(ray.origin, vec_mul(ray.direction, t_hit));
			base = pl->color;
			alt = opposite_color(base);
			record->hit_point = hit_point;
			record->normal = pl->normal;
			if (pl->normal.y != 0 && pl->checkerboard)
				*color = get_checkerboard_color_y(hit_point, 0.5, base, alt);
			else if (pl->normal.x != 0 && pl->checkerboard)
				*color = get_checkerboard_color_x(hit_point, 0.5, base, alt);
			else if (pl->normal.z != 0 && pl->checkerboard)
				*color = get_checkerboard_color_z(hit_point, 0.5, base, alt);
			else
				*color = base;
		}
		i++;
	}
}

void	find_closest_sphere(t_ray ray, t_data *data, t_color *color,
		t_hit_record *record)
{
	int		i;
	double	t_hit;
	t_vec3	hit_point;
	t_vec3	normal;

	i = 0;
	while (i < data->scene->sphere_count)
	{
		t_hit = 0.0;
		if (hit_sphere(&data->scene->spheres[i], ray, &t_hit)
			&& t_hit < record->t && t_hit > 0.001)
		{
			record->t = t_hit;
			*color = data->scene->spheres[i].color;
			record->sphere_index = i;
			record->plane_index = -1;
			record->cylinder_index = -1;
			hit_point = vec_add(ray.origin, vec_mul(ray.direction, t_hit));
			normal = vec_normalize(vec_sub(hit_point,
						data->scene->spheres[i].center));
			record->normal = normal;
			record->hit_point = hit_point;
			if (data->scene->spheres[i].checkerboard)
				*color = get_sphere_checker_color(hit_point,
						data->scene->spheres[i].center,
						data->scene->spheres[i].radius, 3.0,
						data->scene->spheres[i].color,
						opposite_color(data->scene->spheres[i].color));
		}
		i++;
	}
}

void	find_closest_cylinder(t_ray ray, t_data *data, t_color *color,
		t_hit_record *record)
{
	int			i;
	double		t_hit;
	t_vec3		hit_point;
	t_cylinder	*cy;
	t_vec3		cp;
	double		proj;
	t_vec3		normal;

	i = 0;
	while (i < data->scene->cylinder_count)
	{
		t_hit = 0.0;
		if (hit_cylinder(&data->scene->cylinders[i], ray, &t_hit)
			&& t_hit < record->t && t_hit > 0.001)
		{
			record->t = t_hit;
			*color = data->scene->cylinders[i].color;
			record->cylinder_index = i;
			record->sphere_index = -1;
			record->plane_index = -1;
			hit_point = vec_add(ray.origin, vec_mul(ray.direction, t_hit));
			cy = &data->scene->cylinders[i];
			cp = vec_sub(hit_point, cy->center);
			proj = vec_dot(cp, cy->direction);
			normal = vec_normalize(vec_sub(cp, vec_mul(cy->direction, proj)));
			record->normal = normal;
			record->hit_point = hit_point;
			if (data->scene->cylinders[i].checkerboard)
				*color = get_cylinder_checker_color(hit_point,
						&data->scene->cylinders[i], 1.0, 10.0, 1.0,
						data->scene->cylinders[i].color,
						opposite_color(data->scene->cylinders[i].color));
		}
		i++;
	}
}

void	find_closest_intersection(t_ray ray, t_data *data, t_color *color,
		t_hit_record *record)
{
	find_closest_plane(ray, data, color, record);
	find_closest_sphere(ray, data, color, record);
	find_closest_cylinder(ray, data, color, record);
}

int	is_shadow_plane(t_vec3 point, t_light light, t_data *data, double t_hit)
{
	t_vec3	light_dir;
	double	light_distance;
	t_ray	shadow_ray;
	int		i;

	light_dir = vec_normalize(vec_sub(light.pos, point));
	light_distance = vec_len2(vec_sub(light.pos, point));
	shadow_ray = (t_ray){.origin = vec_add(point, vec_mul(light_dir, 1e-4)),
		.direction = light_dir};
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
	shadow_ray = (t_ray){.origin = vec_add(point, vec_mul(light_dir, 1e-4)),
		.direction = light_dir};
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
	shadow_ray = (t_ray){.origin = vec_add(point, vec_mul(light_dir, 1e-4)),
		.direction = light_dir};
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
	shadowed = 0;
	shadowed = is_shadow_plane(point, light, data, t_hit);
	shadowed |= is_shadow_sphere(point, light, data, t_hit);
	shadowed |= is_shadow_cylinder(point, light, data, t_hit);
	return (shadowed);
}

t_color	apply_lighting(t_color base, t_vec3 hit_point, t_vec3 normal,
		t_light light, t_data *data)
{
	t_vec3	light_dir;
	t_vec3	view_dir;
	double	ambient_strength;
	double	diffuse_strength;
	double	specular_strength;
	double	shininess;
	double	r;
	double	g;
	double	b;
	t_vec3	reflect_dir;
	double	spec;

	light_dir = vec_normalize(vec_sub(light.pos, hit_point));
	view_dir = vec_normalize(vec_sub(data->scene->camera.pos, hit_point));
	ambient_strength = data->scene->ambient.brightness;
	diffuse_strength = 0.0;
	specular_strength = 0.5;
	shininess = 64.0;
	r = base.r * ambient_strength * light.color.r / 255.0;
	g = base.g * ambient_strength * light.color.g / 255.0;
	b = base.b * ambient_strength * light.color.b / 255.0;
	if (!is_in_shadow(hit_point, light, data))
	{
		diffuse_strength = fmax(vec_dot(normal, light_dir), 0.0);
		reflect_dir = vec_reflect(vec_mul(light_dir, -1), normal);
		spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), shininess);
		r += base.r * diffuse_strength * light.brightness * light.color.r
			/ 255.0;
		g += base.g * diffuse_strength * light.brightness * light.color.g
			/ 255.0;
		b += base.b * diffuse_strength * light.brightness * light.color.b
			/ 255.0;
		r += specular_strength * spec * light.color.r;
		g += specular_strength * spec * light.color.g;
		b += specular_strength * spec * light.color.b;
	}
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((t_color){(int)r, (int)g, (int)b});
}

t_color	trace_ray(t_ray ray, t_data *data)
{
	t_color			final;
	t_color			base;
	t_hit_record	record;
	int				i;
	t_light			light;
	t_color			light_result;

	final = (t_color){0, 0, 0};
	base = (t_color){100, 100, 100};
	record = (t_hit_record){.t = INFINITY, .sphere_index = -1, .plane_index = \
		-1, .cylinder_index = -1, .normal = {0, 0, 0}};
	find_closest_intersection(ray, data, &base, &record);
	if (record.t < INFINITY)
	{
		i = 0;
		while (i < data->scene->light_count)
		{
			light = data->scene->lights[i];
			light_result = apply_lighting(base, record.hit_point, record.normal,
					light, data);
			final.r += light_result.r;
			final.g += light_result.g;
			final.b += light_result.b;
			i++;
		}
		if (final.r > 255)
			final.r = 255;
		if (final.g > 255)
			final.g = 255;
		if (final.b > 255)
			final.b = 255;
	}
	else
		final = base;
	return (final);
}

t_ray	generate_camera_ray(t_data *data, int x, int y, int sx, int sy)
{
	double	u;
	double	v;
	double	scale;
	double	px;
	double	py;
	t_vec3	dir;

	u = (x + (sx + 0.5) / SAMPLES) / WIDTH;
	v = (y + (sy + 0.5) / SAMPLES) / HEIGHT;
	scale = tan(data->scene->camera.fov * 0.5 * M_PI / 180.0);
	px = (2 * u - 1) * data->scene->camera.aspect_ratio * scale;
	py = (1 - 2 * v) * scale;
	dir = vec_normalize(vec_add(vec_add(vec_mul(data->scene->camera.right, px),
					vec_mul(data->scene->camera.up, py)),
				data->scene->camera.dir));
	return (create_ray(data->scene->camera.pos, dir));
}

void	render_pixel(t_data *data, int x, int y)
{
	int		r;
	int		g;
	int		b;
	int		sy;
	int		sx;
	t_ray	ray;
	t_color	sample;
	t_color	final_color;

	r = 0;
	g = 0;
	b = 0;
	sy = 0;
	while (sy < SAMPLES)
	{
		sx = 0;
		while (sx < SAMPLES)
		{
			ray = generate_camera_ray(data, x, y, sx, sy);
			sample = trace_ray(ray, data);
			r += sample.r;
			g += sample.g;
			b += sample.b;
			sx++;
		}
		sy++;
	}
	final_color = (t_color){r / (SAMPLES * SAMPLES), g / (SAMPLES * SAMPLES), b
		/ (SAMPLES * SAMPLES)};
	put_pixel(data, x, y, final_color);
}

void	*render_thread(void *arg)
{
	t_thread_data	*td;
	int				x;
	int				y;

	td = (t_thread_data *)arg;
	y = td->start_y;
	while (y < td->end_y)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixel(td->data, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

void	render(t_data *data)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				slice;
	int				i;
	double			elapsed_time;
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	slice = HEIGHT / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		thread_data[i].start_y = i * slice;
		if (i == NUM_THREADS - 1)
			thread_data[i].end_y = HEIGHT;
		else
			thread_data[i].end_y = (i + 1) * slice;
		thread_data[i].data = data;
		pthread_create(&threads[i], NULL, render_thread, &thread_data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	gettimeofday(&end, NULL);
	elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)
		/ 1000000.0;
	printf("Elapsed time: %.3f seconds\n", elapsed_time);
}
