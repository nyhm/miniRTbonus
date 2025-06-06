/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 07:55:47 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/05 06:33:16 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rotate_camera_yaw(t_camera *cam, double angle)
{
	t_vec3	world_up;

	world_up.x = 0;
	world_up.y = 1;
	world_up.z = 0;
	if (cam->up.y < 0)
		world_up.y = -1;
	cam->dir = vec_normalize(vec_rotate(cam->dir, world_up, angle));
	cam->right = vec_normalize(vec_cross(cam->dir, world_up));
	cam->up = vec_normalize(vec_cross(cam->right, cam->dir));
}

void	rotate_camera_pitch(t_camera *cam, double angle)
{
	cam->dir = vec_normalize(vec_rotate(cam->dir, cam->right, angle));
	cam->up = vec_normalize(vec_cross(cam->right, cam->dir));
}

void	arrow_keys(t_data *data, int keycode)
{
	if (keycode == KEY_UP)
		rotate_camera_pitch(&data->scene->camera, ROTATE_SPEED);
	else if (keycode == KEY_DOWN)
		rotate_camera_pitch(&data->scene->camera, -ROTATE_SPEED);
	else if (keycode == KEY_RIGHT)
		rotate_camera_yaw(&data->scene->camera, -ROTATE_SPEED);
	else if (keycode == KEY_LEFT)
		rotate_camera_yaw(&data->scene->camera, ROTATE_SPEED);
}

void	move_forward(t_data *data, int keycode)
{
	if (keycode == KEY_W)
	{
		data->scene->camera.pos = vec_add(data->scene->camera.pos,
				vec_mul(data->scene->camera.dir, MOVE_SPEED));
		data->scene->camera.screen_center = \
				vec_add(data->scene->camera.screen_center,
				vec_mul(data->scene->camera.dir, MOVE_SPEED));
	}
	else if (keycode == KEY_S)
	{
		data->scene->camera.pos = vec_add(data->scene->camera.pos,
				vec_mul(data->scene->camera.dir, -MOVE_SPEED));
		data->scene->camera.screen_center = \
				vec_add(data->scene->camera.screen_center,
				vec_mul(data->scene->camera.dir, -MOVE_SPEED));
	}
}

void	move_side(t_data *data, int keycode)
{
	if (keycode == KEY_A)
	{
		data->scene->camera.pos = vec_add(data->scene->camera.pos,
				vec_mul(data->scene->camera.right, -MOVE_SPEED));
		data->scene->camera.screen_center = \
				vec_add(data->scene->camera.screen_center,
				vec_mul(data->scene->camera.right, -MOVE_SPEED));
	}
	else if (keycode == KEY_D)
	{
		data->scene->camera.pos = vec_add(data->scene->camera.pos,
				vec_mul(data->scene->camera.right, MOVE_SPEED));
		data->scene->camera.screen_center = \
				vec_add(data->scene->camera.screen_center,
				vec_mul(data->scene->camera.right, MOVE_SPEED));
	}
}
