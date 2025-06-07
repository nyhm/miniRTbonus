/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:55:39 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 19:59:44 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

void		set_p_checker(t_plane *p, char ***tokens);
static void	plane_check(t_plane plane);
static void	new_plane(t_scene *scene, t_plane plane);
void		parse_plane(t_scene *scene, char ***tokens);

void	set_p_checker(t_plane *p, char ***tokens)
{
	if ((*tokens)[4] && (ft_strcmp((*tokens)[4], "checkerboard") == 0 \
			|| ft_strcmp((*tokens)[4], "checkerboard\n") == 0))
	{
		p->checkerboard = 1;
		*tokens += 5;
	}
	else
	{
		p->checkerboard = 0;
		*tokens += 4;
	}
}

static void	plane_check(t_plane plane)
{
	if (vec_len2(plane.normal) == 0)
		ft_error("Error: plane normal cannot be zero vector\n");
	if (plane.point.x < -1000 || plane.point.x > 1000 || plane.point.y < -1000 \
			|| plane.point.y > 1000 || plane.point.z < -1000 \
				|| plane.point.z > 1000)
		ft_error("Error: plane point must be between -1000 and 1000\n");
	if (plane.color.r < 0 || plane.color.r > 255 || plane.color.g < 0 \
			|| plane.color.g > 255 || plane.color.b < 0 || plane.color.b > 255)
		ft_error("Error: plane color values must be between 0 and 255\n");
}

static void	new_plane(t_scene *scene, t_plane plane)
{
	size_t	new_count;
	t_plane	*new_arr;

	plane_check(plane);
	new_count = scene->plane_count + 1;
	new_arr = malloc(sizeof(t_plane) * new_count);
	if (!new_arr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_memset(new_arr, 0, sizeof(t_plane) * new_count);
	if (scene->planes)
	{
		ft_memcpy(new_arr, scene->planes, sizeof(t_plane) * scene->plane_count);
		free(scene->planes);
	}
	new_arr[scene->plane_count] = plane;
	scene->planes = new_arr;
	scene->plane_count = new_count;
}

void	parse_plane(t_scene *scene, char ***tokens)
{
	t_plane	plane;

	if (count_array(tokens[0]) < 4)
		ft_error("Error: invalid plane line\n");
	if (!(*tokens)[1] || !(*tokens)[2] || !(*tokens)[3] \
			|| ft_isspace((*tokens)[1][0]) || ft_isspace((*tokens)[2][0]) \
				|| ft_isspace((*tokens)[3][0]))
		ft_error("Error: invalid plane line\n");
	plane.point = parse_vec3((*tokens)[1]);
	plane.normal = vec_normalize(parse_vec3((*tokens)[2]));
	plane.color = parse_color((*tokens)[3]);
	set_p_checker(&plane, tokens);
	new_plane(scene, plane);
}
