/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:45:10 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 09:24:27 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"
#include <stdio.h>
#include <string.h>

static void init_data(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        ft_error("Error: mlx_init failed\n");
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
    if (!data->win)
        ft_error("Error: mlx_new_window failed\n");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);//自動的に設定
    if (!data->addr)
        ft_error("Error: mlx_get_data_addr failed\n");
    data->width = WIDTH;
    data->height = HEIGHT;
    data->scene = NULL;
    data->zoom_key = 0;
    data->camera_key = 0;
}

void free_data(t_data *data)
{
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
    if (data->mlx)
        mlx_destroy_display(data->mlx);
    
    if (data->scene->lights)
        free(data->scene->lights);
    if (data->scene->spheres)
        free(data->scene->spheres);
    if (data->scene->planes)
        free(data->scene->planes);
    if (data->scene->cylinders)
        free(data->scene->cylinders);
    
}


void print_controls(void)
{
    ft_write( "=== 操作ガイド ===\n");
    ft_write("\n移動\n");
    ft_write("W : 前に進む\n");
    ft_write("S : 後ろに下がる\n");
    ft_write("A : 左に移動\n");
    ft_write("D : 右に移動\n");
    ft_write("\nカメラ操作\n");
    ft_write("↑ : 上を向く\n");
    ft_write("↓ : 下を向く\n");
    ft_write("← : 左を向く\n");
    ft_write("→ : 右を向く\n");
    ft_write("\nその他の操作\n");
    ft_write( "スペース : 上昇（ジャンプ）\n");
    ft_write("コントロール : 下降\n");
    ft_write("Q : 広角\n");
    ft_write("E : 狭角\n");
    ft_write("ESC : 終了\n");
    ft_write("\n");
}


int main(int argc, char **argv) {
    if (argc != 2) {
        write(2, "Usage: ./miniRT <scene.rt>\n", 27);
        return 1;
    }
    
    t_scene scene = {0};
    parse_rt_file(argv[1], &scene);
    t_data data;
    init_data(&data);
    data.scene = &scene;
    render(&data);
    print_controls();
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_hook(data.win, 2,1L<<0, keyhook, &data);
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_loop(data.mlx);
    return 0;
}
