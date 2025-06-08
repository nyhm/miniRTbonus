/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:59:07 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 10:24:29 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static void	set_c_checker(t_cylinder *cy, char ***tokens);
static void	cy_check(t_cylinder cy);
static void	new_cy(t_scene *scene, t_cylinder cy);
void		parse_cylinder(t_scene *scene, char ***tokens);

static void	set_c_checker(t_cylinder *cy, char ***tokens)
{
	int	i;

	cy->bump_map = 0;
	cy->checkerboard = 0;
	i = 6;
	while (i <= 8 && (*tokens)[i])
	{
		if ((ft_strcmp((*tokens)[i], "bump_map") == 0 || \
			ft_strcmp((*tokens)[i], "bump_map\n") == 0) && !cy->bump_map)
			cy->bump_map = 1;
		else if ((ft_strcmp((*tokens)[i], "checkerboard") == 0 || \
			ft_strcmp((*tokens)[i], "checkerboard\n") == 0) && \
			!cy->checkerboard)
			cy->checkerboard = 1;
		else if ((*tokens)[i] && !ft_isspace((*tokens)[i][0]))
		{
			ft_putstr_fd("Error: invalid texture identifier for cylinder: ", 2);
			ft_putendl_fd((*tokens)[i], 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	cy_check(t_cylinder cy)
{
	if (!is_unit_vector(cy.direction))
		ft_error("Error: orientation vector is not normalized\n");
	if (vec_len2(cy.direction) == 0)
		ft_error("Error: cylinder direction cannot be zero vector\n");
	if (cy.radius <= 0)
		ft_error("Error: cylinder radius must be greater than 0\n");
	if (cy.height <= 0)
		ft_error("Error: cylinder height must be greater than 0\n");
}

static void	new_cy(t_scene *scene, t_cylinder cy)
{
	t_cylinder	*new_arr;
	size_t		new_count;

	cy_check(cy);
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
		ft_memcpy(new_arr, scene->cylinders, sizeof(t_cylinder)
			* scene->cylinder_count);
		free(scene->cylinders);
	}
	new_arr[scene->cylinder_count] = cy;
	scene->cylinders = new_arr;
	scene->cylinder_count = new_count;
}

void	parse_cylinder(t_scene *scene, char ***tokens)
{
	t_cylinder	cy;

	if (count_array(tokens[0]) < 6)
		ft_error("Error: invalid cylinder line\n");
	if (!(*tokens)[1] || !(*tokens)[2] || !(*tokens)[3] || !(*tokens)[4]
		|| !(*tokens)[5] || ft_isspace((*tokens)[1][0])
		|| ft_isspace((*tokens)[2][0]) || ft_isspace((*tokens)[4][0])
		|| ft_isspace((*tokens)[5][0]))
		ft_error("Error: invalid cylinder line\n");
	cy.center = parse_vec3((*tokens)[1]);
	cy.direction = parse_vec3((*tokens)[2]);
	cy.radius = atof((*tokens)[3]) / 2.0;
	cy.height = atof((*tokens)[4]);
	cy.color = parse_color((*tokens)[5]);
	set_c_checker(&cy, tokens);
	new_cy(scene, cy);
}
