/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:55:39 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/05 18:22:50 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	plane_check(t_plane plane, t_plane *new_arr);
void	new_plane(t_scene *scene, t_plane plane);
void	parse_plane(t_scene *scene, char **tokens);
void	plane_token(t_scene *scene, char ***tokens, size_t count_tokens);

void	plane_check(t_plane plane, t_plane *new_arr)
{
	if (vec_len2(plane.normal) == 0)
	{
		free(new_arr);
		ft_error("Error: plane normal cannot be zero vector\n");
	}
	if (plane.point.x < -1000 || plane.point.x > 1000 || \
		plane.point.y < -1000 || plane.point.y > 1000 || \
		plane.point.z < -1000 || plane.point.z > 1000)
	{
		free(new_arr);
		ft_error("Error: plane point must be between -1000 and 1000\n");
	}
}

void	new_plane(t_scene *scene, t_plane plane)
{
	size_t	new_count;
	t_plane	*new_arr;

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
	plane_check(plane, new_arr);
	new_arr[scene->plane_count] = plane;
	scene->planes = new_arr;
	scene->plane_count = new_count;
}

void	parse_plane(t_scene *scene, char **tokens)
{
	t_plane	plane;

	if (!tokens[1] || !tokens[2] || !tokens[3] || ft_isspace(tokens[1][0]) \
		|| ft_isspace(tokens[2][0]) || ft_isspace(tokens[3][0]))
		ft_error("Error: invalid plane line\n");
	plane.point = parse_vec3(tokens[1]);
	plane.normal = vec_normalize(parse_vec3(tokens[2]));
	plane.color = parse_color(tokens[3]);
	new_plane(scene, plane);
}

void	plane_token(t_scene *scene, char ***tokens, size_t count_tokens)
{
	if (count_tokens < 4)
		ft_error("Error: invalid plane line\n");
	parse_plane(scene, *tokens);
	*tokens += 4;
}
