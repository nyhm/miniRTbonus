/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:00:35 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 06:09:26 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

void	parse_ambient(t_scene *scene, char ***tokens)
{
	if (scene->ambient_count++)
		ft_error("Error: duplicate ambient\n");
	if (count_array(tokens[0]) < 3)
		ft_error("Error: invalid ambient line\n");
	if (!(*tokens)[1] || !(*tokens)[2] || ft_isspace((*tokens)[1][0])
		|| ft_isspace((*tokens)[2][0]))
		ft_error("Error: invalid ambient line\n");
	if ((*tokens)[3] && !ft_isspace((*tokens)[3][0]))
	{
		ft_putstr_fd("Error: invalid texture identifier for ambient: ", 2);
		ft_putendl_fd((*tokens)[3], 2);
		exit(EXIT_FAILURE);
	}
	scene->ambient.brightness = ft_atof((*tokens)[1]);
	scene->ambient.color = parse_color((*tokens)[2]);
}
