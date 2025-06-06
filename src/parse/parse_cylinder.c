/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:59:07 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/05 18:22:41 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	cy_token(t_scene *scene, char ***tokens, size_t count_tokens);
void	cy_check(t_cylinder cy, t_cylinder *new_arr);
void	parse_cylinder(t_scene *scene, char **tokens);
void	new_cy(t_scene *scene, t_cylinder cy);

void	cy_check(t_cylinder cy, t_cylinder *new_arr)
{
	if (vec_len2(cy.direction) == 0)
	{
		free(new_arr);
		ft_error("Error: cylinder direction cannot be zero vector\n");
	}
	if (cy.center.x < -1000 || cy.center.x > 1000 || \
		cy.center.y < -1000 || cy.center.y > 1000 || \
		cy.center.z < -1000 || cy.center.z > 1000)
	{
		free(new_arr);
		ft_error("Error: cylinder center must be between -1000 and 1000\n");
	}
	if (cy.radius <= 0)
	{
		free(new_arr);
		ft_error("Error: cylinder radius must be greater than 0\n");
	}
	if (cy.height <= 0)
	{
		free(new_arr);
		ft_error("Error: cylinder height must be greater than 0\n");
	}
}

void	new_cy(t_scene *scene, t_cylinder cy)
{
	t_cylinder	*new_arr;
	size_t		new_count;

	new_count = scene->cylinder_count + 1;
	new_arr = malloc(sizeof(t_cylinder) * new_count);
	if (!new_arr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_memset(new_arr, 0, sizeof(t_cylinder) * new_count);
	if (scene->cylinders)
	{
		ft_memcpy(new_arr, scene->cylinders, sizeof(t_cylinder) \
		* scene->cylinder_count);
		free(scene->cylinders);
	}
	cy_check(cy, new_arr);
	new_arr[scene->cylinder_count] = cy;
	scene->cylinders = new_arr;
	scene->cylinder_count = new_count;
}

void	parse_cylinder(t_scene *scene, char **tokens)
{
	t_cylinder	cy;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5] || \
		ft_isspace(tokens[1][0]) || ft_isspace(tokens[2][0]) || \
		ft_isspace(tokens[4][0]) || ft_isspace(tokens[5][0]))
		ft_error("Error: invalid cylinder line\n");
	cy.center = parse_vec3(tokens[1]);
	cy.direction = vec_normalize(parse_vec3(tokens[2]));
	cy.radius = atof(tokens[3]) / 2.0;
	cy.height = atof(tokens[4]);
	cy.color = parse_color(tokens[5]);
	new_cy(scene, cy);
}

void	cy_token(t_scene *scene, char ***tokens, size_t count_tokens)
{
	if (count_tokens < 6)
		ft_error("Error: invalid cylinder line\n");
	parse_cylinder(scene, *tokens);
	*tokens += 6;
}
