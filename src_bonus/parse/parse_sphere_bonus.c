/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:57:59 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 20:24:48 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

void		set_s_checker(t_sphere *s, char ***tokens);
static void	sphere_check(t_sphere s);
static void	new_sphere(t_scene *scene, t_sphere s);
void		parse_sphere(t_scene *scene, char ***tokens);

void	set_s_checker(t_sphere *s, char ***tokens) //static
{
	if ((*tokens)[4] && (ft_strcmp((*tokens)[4], "checkerboard") == 0 \
			|| ft_strcmp((*tokens)[4], "checkerboard\n") == 0))
	{
		s->checkerboard = 1;
		*tokens += 5;
	}
	else
	{
		s->checkerboard = 0;
		*tokens += 4;
	}
}

static void	sphere_check(t_sphere s)
{
	if (s.radius <= 0)
		ft_error("Error: sphere radius must be greater than 0\n");
	if (s.center.x < -1000 || s.center.x > 1000 || s.center.y < -1000 \
			|| s.center.y > 1000 || s.center.z < -1000 || s.center.z > 1000)
		ft_error("Error: sphere center must be between -1000 and 1000\n");
	if (s.color.r < 0 || s.color.r > 255 || s.color.g < 0 || s.color.g > 255 \
			|| s.color.b < 0 || s.color.b > 255)
		ft_error("Error: sphere color values must be between 0 and 255\n");
}

static void	new_sphere(t_scene *scene, t_sphere s)
{
	size_t		new_count;
	t_sphere	*new_arr;

	sphere_check(s);
	new_count = scene->sphere_count + 1;
	new_arr = malloc(sizeof(t_sphere) * new_count);
	if (!new_arr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_memset(new_arr, 0, sizeof(t_sphere) * new_count);
	if (scene->spheres && scene->sphere_count > 0)
	{
		ft_memcpy(new_arr, scene->spheres, sizeof(t_sphere) \
			* scene->sphere_count);
		free(scene->spheres);
	}
	new_arr[scene->sphere_count] = s;
	scene->spheres = new_arr;
	scene->sphere_count = new_count;
}

void	parse_sphere(t_scene *scene, char ***tokens)
{
	t_sphere	s;

	if (count_array(tokens[0]) < 4)
		ft_error("Error: invalid sphere line\n");
	if (!(*tokens)[1] || !(*tokens)[2] || !(*tokens)[3] \
			|| ft_isspace((*tokens)[1][0]) || ft_isspace((*tokens)[2][0]) \
				|| ft_isspace((*tokens)[3][0]))
		ft_error("Error: invalid sphere line\n");
	s.center = parse_vec3((*tokens)[1]);
	s.radius = ft_atof((*tokens)[2]) / 2.0;
	s.color = parse_color((*tokens)[3]);
	set_s_checker(&s, tokens);
	new_sphere(scene, s);
}
