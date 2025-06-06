/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 03:30:36 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/05 06:32:43 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	move_height(t_data *data, int keycode)
{
	if (keycode == KEY_SPACE)
	{
		if (data->scene->camera.up.y < 0)
			data->scene->camera.pos.y -= MOVE_SPEED;
		else
			data->scene->camera.pos.y += MOVE_SPEED;
	}
	else if (keycode == KEY_CTRL || keycode == KEY_CTRL2)
	{
		if (data->scene->camera.up.y < 0)
			data->scene->camera.pos.y += MOVE_SPEED;
		else
			data->scene->camera.pos.y -= MOVE_SPEED;
	}
}

void	fov_key(t_data *data, int keycode)
{
	if (keycode == KEY_Q)
	{
		data->scene->camera.fov += 3.0;
		if (data->scene->camera.fov > 180.0)
			data->scene->camera.fov = 180.0;
	}
	else if (keycode == KEY_E)
	{
		data->scene->camera.fov -= 3.0;
		if (data->scene->camera.fov < 1.0)
			data->scene->camera.fov = 1.0;
	}
	data->scene->camera.aspect_ratio = (double)data->width
		/ (double)data->height;
	data->scene->camera.horizontal = vec_scale(data->scene->camera.right,
			tan(data->scene->camera.fov * M_PI / 360.0) * 2);
	data->scene->camera.vertical = vec_scale(data->scene->camera.up,
			tan(data->scene->camera.fov * M_PI / 360.0) * 2);
}

int	keyhook(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	else if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT
		|| keycode == KEY_RIGHT)
		arrow_keys(data, keycode);
	else if (keycode == KEY_W || keycode == KEY_S)
		move_forward(data, keycode);
	else if (keycode == KEY_A || keycode == KEY_D)
		move_side(data, keycode);
	else if (keycode == KEY_SPACE || keycode == KEY_CTRL
		|| keycode == KEY_CTRL2)
		move_height(data, keycode);
	else if (keycode == KEY_Q || keycode == KEY_E)
		fov_key(data, keycode);
	else
		printf("デバック用Other key pressed: %d\n", keycode);
	render(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_data(data);
	exit(0);
	return (0);
}
