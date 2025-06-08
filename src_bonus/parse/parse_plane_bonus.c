/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:55:39 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 16:17:22 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static void	set_p_checker(t_plane *p, char ***tokens);
static void	new_plane(t_scene *scene, t_plane plane);
void		parse_plane(t_scene *scene, char ***tokens);

static void	set_p_checker(t_plane *p, char ***tokens)
{
	int	i;

	p->bump_map = 0;
	p->checkerboard = 0;
	i = 4;
	while (i <= 6 && (*tokens)[i])
	{
		if ((ft_strcmp((*tokens)[i], "bump_map") == 0 || \
			ft_strcmp((*tokens)[i], "bump_map\n") == 0) && !p->bump_map)
			p->bump_map = 1;
		else if ((ft_strcmp((*tokens)[i], "checkerboard") == 0 || \
			ft_strcmp((*tokens)[i], "checkerboard\n") == 0) && !p->checkerboard)
			p->checkerboard = 1;
		else if ((*tokens)[i] && !ft_isspace((*tokens)[i][0]))
		{
			ft_putstr_fd("Error: invalid texture identifier for plane: ", 2);
			ft_putendl_fd((*tokens)[i], 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	new_plane(t_scene *scene, t_plane plane)
{
	size_t	new_count;
	t_plane	*new_arr;

	if (!is_unit_vector(plane.normal))
		ft_error("Error: orientation vector is not normalized\n");
	if (vec_len2(plane.normal) == 0)
		ft_error("Error: plane normal cannot be zero vector\n");
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
	plane.normal = parse_vec3((*tokens)[2]);
	plane.color = parse_color((*tokens)[3]);
	set_p_checker(&plane, tokens);
	new_plane(scene, plane);
}
