/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:59:18 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/05 06:33:49 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
#define MINIRT_BONUS_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> //デバック用
#include <time.h>//デバック用
#include <sys/time.h> //デバック用
#include <math.h>
#include <mlx.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include <pthread.h>

#define WIDTH 800
#define HEIGHT 600
#define BUFFER_SIZE 42
#define MOVE_SPEED 1
#define ROTATE_SPEED 0.3 // カメラの回転速度
#define KEY_ESC 65307 // Escキー
#define KEY_UP 65362 // 上矢印キー
#define KEY_DOWN 65364 // 下矢印キー
#define KEY_LEFT 65361 // 左矢印キー
#define KEY_RIGHT 65363 // 右矢印キー
#define KEY_W 119 // Wキー
#define KEY_S 115 // Sキー
#define KEY_A 97 // Aキー
#define KEY_D 100 // Dキー
#define KEY_Q 113 // Qキー
#define KEY_E 101 // Eキー
#define KEY_SPACE 32 // スペースキー
#define KEY_CTRL 65507 // Ctrlキー
#define KEY_CTRL2 65508// Ctrlキー

#define NUM_THREADS 16
#define SAMPLES 1



typedef struct s_vec3 {//3次元ベクトル
    double x, y, z;
} t_vec3;

typedef struct s_color {//色
    int r; // 赤成分 (0-255)
    int g; // 緑成分 (0-255)
    int b; // 青成分 (0-255)
} t_color;

typedef struct s_plane {//平面
    t_vec3 point;     // 平面上の1点
    t_vec3 normal;    // 法線ベクトル（正規化されている想定）
    t_color color; 
    int checkerboard; // チェッカーボードの有無（1: 有効, 0: 無効）
} t_plane;

typedef struct s_cylinder {//円柱
    t_vec3 center;    // 底面中心
    t_vec3 direction; // 方向ベクトル（正規化されている想定）
    double radius;    // 半径
    double height;    // 高さ
    t_color color; 
    int checkerboard; // チェッカーボードの有無（1: 有効, 0: 無効）
} t_cylinder;

typedef struct s_ray {//光線
    t_vec3 origin;    // 光線の始点
    t_vec3 direction; // 光線の方向ベクトル（正規化されている想定）
} t_ray;


typedef struct s_camera
{
    t_vec3 pos;       // カメラの位置
    t_vec3 dir;      // 視線の方向（正規化ベクトル）
    t_vec3 up;             // 上方向（正規化ベクトル）
    t_vec3 right;          // 右方向（direction × up）

    double fov;            // 視野角（ラジアン）
    double aspect_ratio;   // アスペクト比（例：16.0 / 9.0）

    t_vec3 screen_center;  // カメラの前方にあるスクリーンの中心
    t_vec3 horizontal;     // スクリーンの横ベクトル（幅方向）
    t_vec3 vertical;       // スクリーンの縦ベクトル（高さ方向）
} t_camera;


typedef struct s_light {//光源
    t_vec3 pos; // 光源の位置
    double brightness; // 光源の明るさ（0.0〜1.0）
    t_color color; 
} t_light;

typedef struct s_sphere {//球
    t_vec3 center;  // 球の中心
    double radius;  // 球の半径
    t_color color; 
    int checkerboard; // チェッカーボードの有無（1: 有効, 0: 無効）
} t_sphere;

typedef struct s_ambient {//環境光
    double brightness; // 環境光の明るさ（0.0〜1.0）
    t_color color; 
} t_ambient;


typedef struct s_scene {//シーン
    t_ambient ambient; // 環境光
    t_camera camera;    // カメラ

    t_light *lights;   // 光源
    int light_count; // 光源の数

    t_sphere *spheres; // 球の配列
    int sphere_count; // 球の数
    
    t_plane *planes; // 平面の配列
    int plane_count; // 平面の数

    t_cylinder *cylinders; // 円柱の配列
    int cylinder_count; // 円柱の数

    int background_color; // 背景色
    
    int anti_aliasing; // アンチエイリアシングの有無（1: 有効, 0: 無効）
} t_scene;


typedef struct s_data {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_length;
    int endian;

    int width;
    int height;
    int zoom_key;
    int camera_key;
    int fov_key;
    int is_rendered;
    unsigned int frame_count;
    t_scene *scene;
} t_data;


typedef struct s_hit_record {
    double t;
    int sphere_index;
    int plane_index;
    int cylinder_index;
    t_vec3 normal; // ヒット地点の法線ベクトル
    t_vec3 hit_point; // ヒット地点の座標
} t_hit_record;

typedef struct s_thread_data {
    int start_y;
    int end_y;
    t_data *data;
} t_thread_data;


void free_data(t_data *data);
// 関数宣言
// vec3.c
t_vec3 vec3(double x, double y, double z);
t_vec3 vec_add(t_vec3 a, t_vec3 b);
t_vec3 vec_sub(t_vec3 a, t_vec3 b);
t_vec3 vec_mul(t_vec3 v, double t);
double vec_dot(t_vec3 a, t_vec3 b);
t_vec3 vec_normalize(t_vec3 v);
t_vec3 vec_scale(t_vec3 v, double s);
t_vec3 vec_cross(t_vec3 a, t_vec3 b);
t_vec3 vec_reflect(t_vec3 I, t_vec3 N);
double vec_len2(t_vec3 v);
// ray.c
t_ray create_ray(t_vec3 origin, t_vec3 direction);

// hit.c
int hit_sphere(t_sphere *s, t_ray ray, double *t_hit);
int hit_plane(t_plane *p, t_ray ray, double *t_hit);
int hit_cylinder(t_cylinder *cy, t_ray ray, double *t_hit);

// parse.c
void parse_rt_file(const char *filename, t_scene *scene);
void dispatch_parse(t_scene *scene, char **tokens);
t_color parse_color(char *str);
// render.c
void render(t_data *data);
size_t	count_array(char **arr);

// utils.c
void free_split(char **arr);
t_vec3 parse_vec3(const char *str);
double ft_atof(char *str);
int ft_count_words(const char *str, char delim);
int ft_strcmp(const char *s1, const char *s2);
int ft_isspace(int c);
void ft_error(const char *msg);
void ft_write(const char *str);
// key_hook.c
int				close_window(void *param);
int				keyhook(int keycode, t_data *data);
void	rotate_camera_yaw(t_camera *cam, double angle);
void	rotate_camera_pitch(t_camera *cam, double angle);
void			arrow_keys(t_data *data, int keycode);
void			move_forward(t_data *data, int keycode);
void			move_side(t_data *data, int keycode);
void			move_height(t_data *data, int keycode);
void			fov_key(t_data *data, int keycode);
// get_next_line.c
char	*get_next_line(int fd);

#endif
