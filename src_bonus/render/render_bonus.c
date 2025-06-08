/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:47:06 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 16:14:56 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static void	put_pixel(t_data *data, int x, int y, t_color color);
static void	render_pixel(t_data *data, t_coord coord);
void		render(t_data *data);

static void	put_pixel(t_data *data, int x, int y, t_color color)
{
	char	*dst;
	int		pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = (color.r << 16) | (color.g << 8) | (color.b);
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = pixel;
}

static void	render_pixel(t_data *data, t_coord coord)
{
	t_color	color;
	t_ray	ray;
	t_color	sample;
	t_color	final_color;

	color = (t_color){0, 0, 0};
	coord.sy = 0;
	while (coord.sy < SAMPLES)
	{
		coord.sx = 0;
		while (coord.sx < SAMPLES)
		{
			ray = generate_camera_ray(data, coord);
			sample = trace_ray(ray, data);
			color.r += sample.r;
			color.g += sample.g;
			color.b += sample.b;
			coord.sx++;
		}
		coord.sy++;
	}
	final_color = (t_color){color.r / (SAMPLES * SAMPLES), color.g / (SAMPLES \
			* SAMPLES), color.b / (SAMPLES * SAMPLES)};
	put_pixel(data, coord.x, coord.y, final_color);
}

void	render(t_data *data)
{
	t_coord	coord;

	coord.y = 0;
	while (coord.y < HEIGHT)
	{
		coord.x = 0;
		while (coord.x < WIDTH)
		{
			render_pixel(data, coord);
			coord.x++;
		}
		coord.y++;
	}
}

// static void	*render_thread(void *arg)
// {
// 	t_thread_data	*td;
// 	t_coord			coord;

// 	td = (t_thread_data *)arg;
// 	coord.y = td->start_y;
// 	while (coord.y < td->end_y)
// 	{
// 		coord.x = 0;
// 		while (coord.x < WIDTH)
// 		{
// 			render_pixel(td->data, coord);
// 			coord.x++;
// 		}
// 		coord.y++;
// 	}
// 	return (NULL);
// }

// void	render(t_data *data)
// {
// 	pthread_t		threads[NUM_THREADS];
// 	t_thread_data	thread_data[NUM_THREADS];
// 	int				slice;
// 	int				i;
// 	int				ret;

// 	slice = HEIGHT / NUM_THREADS;
// 	i = 0;
// 	while (i < NUM_THREADS)
// 	{
// 		thread_data[i].start_y = i * slice;
// 		if (i == NUM_THREADS - 1)
// 			thread_data[i].end_y = HEIGHT;
// 		else
// 			thread_data[i].end_y = (i + 1) * slice;
// 		thread_data[i].data = data;
// 		ret = pthread_create(&threads[i], NULL, render_thread, &thread_data[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < NUM_THREADS)
// 	{
// 		pthread_join(threads[i], NULL); //上と同様
// 		i++;
// 	}
// }
