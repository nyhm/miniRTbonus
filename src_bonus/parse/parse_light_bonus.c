/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:02:28 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 16:17:32 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static void	new_light(t_scene *scene, t_light light);
void		parse_light(t_scene *scene, char ***tokens);

static void	new_light(t_scene *scene, t_light light)
{
	t_light	*new_arr;
	size_t	new_count;

	if (light.brightness < 0 || light.brightness > 1)
		ft_error("Error: light brightness must be between 0 and 1\n");
	new_count = scene->light_count + 1;
	new_arr = malloc(sizeof(t_light) * new_count);
	if (!new_arr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_memset(new_arr, 0, sizeof(t_light) * new_count);
	if (scene->lights)
	{
		ft_memcpy(new_arr, scene->lights, sizeof(t_light) * scene->light_count);
		free(scene->lights);
	}
	new_arr[scene->light_count] = light;
	scene->lights = new_arr;
	scene->light_count = new_count;
}

void	parse_light(t_scene *scene, char ***tokens)
{
	t_light	light;

	if (count_array(tokens[0]) < 4)
		ft_error("Error: invalid light line\n");
	if (!(*tokens)[1] || !(*tokens)[2] || !(*tokens)[3] \
		|| ft_isspace((*tokens)[1][0]) || ft_isspace((*tokens)[2][0]) \
		|| ft_isspace((*tokens)[3][0]))
		ft_error("Error: invalid light line\n");
	if ((*tokens)[4] && !ft_isspace((*tokens)[4][0]))
	{
		ft_putstr_fd("Error: invalid texture identifier for light: ", 2);
		ft_putendl_fd((*tokens)[4], 2);
		exit(EXIT_FAILURE);
	}
	light.pos = parse_vec3((*tokens)[1]);
	light.brightness = ft_atof((*tokens)[2]);
	light.color = parse_color((*tokens)[3]);
	new_light(scene, light);
}
