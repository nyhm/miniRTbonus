/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:01:34 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/05 18:22:39 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	parse_camera(t_scene *scene, char **tokens);
void	camera_token(t_scene *scene, char ***tokens, size_t count_tokens);

void	camera_token(t_scene *scene, char ***tokens, size_t count_tokens)
{
	if (scene->camera_count++)
		ft_error("Error: duplicate camera\n");
	if (count_tokens < 4)
		ft_error("Error: invalid camera line\n");
	parse_camera(scene, *tokens);
	*tokens += 4;
}

void	parse_camera(t_scene *scene, char **tokens)
{
	t_vec3	world_up;
	double	half_height;

	if (!tokens[1] || !tokens[2] || !tokens[3] || ft_isspace(tokens[1][0]) \
		|| ft_isspace(tokens[2][0]) || ft_isspace(tokens[3][0]))
		ft_error("Error: invalid camera line\n");
	scene->camera.pos = parse_vec3(tokens[1]);
	scene->camera.dir = vec_normalize(parse_vec3(tokens[2]));
	scene->camera.fov = ft_atof(tokens[3]);
	if (vec_len2(scene->camera.dir) == 0)
		ft_error("Error: camera direction cannot be zero vector\n");
	if (scene->camera.fov <= 0 || scene->camera.fov >= 180)
		ft_error("Error: camera FOV must be between 0 and 180 degrees\n");
	scene->camera.aspect_ratio = (double)WIDTH / HEIGHT;
	world_up = (t_vec3){0, 1, 0};
	if (fabs(vec_dot(scene->camera.dir, world_up)) > 0.999)
		world_up = (t_vec3){0, 0, 1};
	scene->camera.right = vec_normalize(vec_cross(scene->camera.dir, world_up));
	scene->camera.up = vec_cross(scene->camera.right, scene->camera.dir);
	scene->camera.screen_center = vec_add(scene->camera.pos, \
		vec_scale(scene->camera.dir, 1.0));
	half_height = tan((scene->camera.fov * M_PI / 180.0) / 2);
	scene->camera.horizontal = vec_scale(scene->camera.right, \
		(scene->camera.aspect_ratio * half_height) * 2);
	scene->camera.vertical = vec_scale(scene->camera.up, half_height * 2);
}
