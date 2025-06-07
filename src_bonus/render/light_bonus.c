/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 07:51:46 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 17:48:46 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static void		calculate_ambient(t_color base, t_ambient ambient,
					t_color_double *color_d);
static void		calculate_diffuse_specular(t_hit_record record, t_light light,
					t_data *data, t_color_double *color_d);
static t_color	finalize_color(t_color_double color_d);

static void	calculate_ambient(t_color base, t_ambient ambient,
		t_color_double *color_d)
{
	color_d->r = base.r * ambient.brightness * ambient.color.r / 255.0;
	color_d->g = base.g * ambient.brightness * ambient.color.g / 255.0;
	color_d->b = base.b * ambient.brightness * ambient.color.b / 255.0;
}

static void	calculate_diffuse_specular(t_hit_record record, t_light light,
		t_data *data, t_color_double *color_d)
{
	t_vec3			light_dir;
	t_vec3			view_dir;
	t_vec3			reflect_dir;
	t_light_calc	calc;

	light_dir = vec_normalize(vec_sub(light.pos, record.hit_point));
	view_dir = vec_normalize(vec_sub(data->scene->camera.pos,
				record.hit_point));
	calc.diffuse_strength = fmax(vec_dot(record.normal, light_dir), 0.0);
	calc.specular_strength = 0.5;
	calc.shininess = 64.0;
	reflect_dir = vec_reflect(vec_mul(light_dir, -1), record.normal);
	calc.spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), calc.shininess);
	color_d->r += record.color.r * calc.diffuse_strength * light.brightness
		* light.color.r / 255.0;
	color_d->g += record.color.g * calc.diffuse_strength * light.brightness
		* light.color.g / 255.0;
	color_d->b += record.color.b * calc.diffuse_strength * light.brightness
		* light.color.b / 255.0;
	color_d->r += calc.specular_strength * calc.spec * light.color.r;
	color_d->g += calc.specular_strength * calc.spec * light.color.g;
	color_d->b += calc.specular_strength * calc.spec * light.color.b;
}

static t_color	finalize_color(t_color_double color_d)
{
	t_color	result;

	if (color_d.r > 255)
		color_d.r = 255;
	if (color_d.g > 255)
		color_d.g = 255;
	if (color_d.b > 255)
		color_d.b = 255;
	result.r = (int)color_d.r;
	result.g = (int)color_d.g;
	result.b = (int)color_d.b;
	return (result);
}

t_color	apply_lighting(t_hit_record record, t_light light, t_data *data)
{
	t_color_double	color_d;

	color_d = (t_color_double){0, 0, 0};
	calculate_ambient(record.color, data->scene->ambient, &color_d);
	if (light.brightness > 0 && !is_in_shadow(record.hit_point, light, data))
		calculate_diffuse_specular(record, light, data, &color_d);
	return (finalize_color(color_d));
}

void	light_set(t_color *dest, t_color src)
{
	dest->r += src.r;
	dest->g += src.g;
	dest->b += src.b;
	if (dest->r > 255)
		dest->r = 255;
	if (dest->g > 255)
		dest->g = 255;
	if (dest->b > 255)
		dest->b = 255;
}
