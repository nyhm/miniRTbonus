/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:57:59 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/05 18:22:53 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	sphere_check(t_sphere s, t_sphere *new_arr);
void	new_sphere(t_scene *scene, t_sphere s);
void	parse_sphere(t_scene *scene, char **tokens);
void	sp_token(t_scene *scene, char ***tokens, size_t count_tokens);

void	sphere_check(t_sphere s, t_sphere *new_arr)
{
	if (s.radius <= 0)
	{
		free(new_arr);
		ft_error("Error: sphere radius must be greater than 0\n");
	}
	if (s.center.x < -1000 || s.center.x > 1000 || \
		s.center.y < -1000 || s.center.y > 1000 || \
		s.center.z < -1000 || s.center.z > 1000)
	{
		free(new_arr);
		ft_error("Error: sphere center must be between -1000 and 1000\n");
	}
}

void	new_sphere(t_scene *scene, t_sphere s)
{
	size_t		new_count;
	t_sphere	*new_arr;

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
		ft_memcpy(new_arr, scene->spheres, \
			sizeof(t_sphere) * scene->sphere_count);
		free(scene->spheres);
	}
	sphere_check(s, new_arr);
	new_arr[scene->sphere_count] = s;
	scene->spheres = new_arr;
	scene->sphere_count = new_count;
}

void	parse_sphere(t_scene *scene, char **tokens)
{
	t_sphere	s;

	if (!tokens[1] || !tokens[2] || !tokens[3] || ft_isspace(tokens[1][0]) \
		|| ft_isspace(tokens[2][0]) || ft_isspace(tokens[3][0]))
		ft_error("Error: invalid sphere line\n");
	s.center = parse_vec3(tokens[1]);
	s.radius = ft_atof(tokens[2]) / 2.0;
	s.color = parse_color(tokens[3]);
	new_sphere(scene, s);
}

void	sp_token(t_scene *scene, char ***tokens, size_t count_tokens)
{
	if (count_tokens < 4)
		ft_error("Error: invalid sphere line\n");
	parse_sphere(scene, *tokens);
	*tokens += 4;
}
