/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:37:28 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 15:49:15 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static void	set_co_checker(t_cone *cone, char ***tokens);
static void	cone_check(t_cone cone);
static void	new_cone(t_scene *scene, t_cone cone);
void		parse_cone(t_scene *scene, char ***tokens);

static void	set_co_checker(t_cone *cone, char ***tokens)
{
	int	i;

	cone->bump_map = 0;
	cone->checkerboard = 0;
	i = 6;
	while (i <= 8 && (*tokens)[i])
	{
		if ((ft_strcmp((*tokens)[i], "bump_map") == 0 || \
			ft_strcmp((*tokens)[i], "bump_map\n") == 0) && !cone->bump_map)
			cone->bump_map = 1;
		else if ((ft_strcmp((*tokens)[i], "checkerboard") == 0 \
				|| ft_strcmp((*tokens)[i], "checkerboard\n") == 0) \
				&& !cone->checkerboard)
			cone->checkerboard = 1;
		else if ((*tokens)[i] && !ft_isspace((*tokens)[i][0]))
		{
			ft_putstr_fd("Error: invalid texture identifier for cone: ", 2);
			ft_putendl_fd((*tokens)[i], 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	cone_check(t_cone cone)
{
	if (vec_len2(cone.direction) == 0)
		ft_error("Error: cone direction cannot be zero vector\n");
	if (cone.height <= 0)
		ft_error("Error: cone height must be greater than 0\n");
	if (cone.angle <= 0 || cone.angle >= 180)
		ft_error("Error: cone angle must be between 0 and 180 degrees\n");
}

static void	new_cone(t_scene *scene, t_cone cone)
{
	t_cone	*new_arr;
	size_t	new_count;

	cone_check(cone);
	new_count = scene->cone_count + 1;
	new_arr = malloc(sizeof(t_cone) * new_count);
	if (!new_arr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_memset(new_arr, 0, sizeof(t_cone) * new_count);
	if (scene->cones)
	{
		ft_memcpy(new_arr, scene->cones, sizeof(t_cone) * scene->cone_count);
		free(scene->cones);
	}
	new_arr[scene->cone_count] = cone;
	scene->cones = new_arr;
	scene->cone_count = new_count;
}

void	parse_cone(t_scene *scene, char ***tokens)
{
	t_cone	cone;

	if (count_array(tokens[0]) < 6)
		ft_error("Error: invalid cone line\n");
	if (!(*tokens)[1] || !(*tokens)[2] || !(*tokens)[3] || !(*tokens)[4]
		|| !(*tokens)[5] || ft_isspace((*tokens)[1][0])
		|| ft_isspace((*tokens)[2][0]) || ft_isspace((*tokens)[4][0])
		|| ft_isspace((*tokens)[5][0]))
		ft_error("Error: invalid cone line\n");
	cone.apex = parse_vec3((*tokens)[1]);
	cone.direction = parse_vec3((*tokens)[2]);
	cone.height = ft_atof((*tokens)[3]);
	cone.angle = ft_atof((*tokens)[4]);
	cone.color = parse_color((*tokens)[5]);
	set_co_checker(&cone, tokens);
	new_cone(scene, cone);
}
