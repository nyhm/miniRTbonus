/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:00:35 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 08:49:48 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

void	ambient_token(t_scene *scene, char ***tokens, size_t count_tokens);
void	parse_ambient(t_scene *scene, char **tokens);

void	parse_ambient(t_scene *scene, char **tokens)
{
	if (!tokens[1] || !tokens[2] || ft_isspace(tokens[1][0]) \
		|| ft_isspace(tokens[2][0]))
		ft_error("Error: invalid ambient line\n");
	scene->ambient.brightness = ft_atof(tokens[1]);
	scene->ambient.color = parse_color(tokens[2]);
}

void	ambient_token(t_scene *scene, char ***tokens, size_t count_tokens)
{
	if (scene->ambient_count++)
		ft_error("Error: duplicate ambient\n");
	if (count_tokens < 3)
		ft_error("Error: invalid ambient line\n");
	parse_ambient(scene, *tokens);
	*tokens += 3;
}
