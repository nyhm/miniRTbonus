/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:59:18 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 11:17:19 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
# define BUFFER_SIZE 42
# define MOVE_SPEED 1
# define ROTATE_SPEED 0.3
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101
# define KEY_SPACE 32
# define KEY_CTRL 65508
# define KEY_CTRL2 65507

# define NUM_THREADS 16
# define SAMPLES 1

typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct s_color_double
{
	double		r;
	double		g;
	double		b;
}				t_color_double;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal;
	t_color		color;
	int			checkerboard;
}				t_plane;

typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		direction;
}				t_ray;

typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		direction;
	double		radius;
	double		height;
	t_color		color;
	int			checkerboard;
}				t_cylinder;

typedef struct s_quadratic
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		sqrt_discriminant;
	double		t0;
	double		t1;
}				t_quadratic;

typedef struct s_cylinder_hit
{
	t_cylinder	*cy;
	t_ray		ray;
	double		*t_candidates;
	int			count;
}				t_cylinder_hit;

typedef struct s_cap_hit
{
	t_vec3		center;
	t_vec3		normal;
	double		radius;
	t_ray		ray;
	double		*t_candidates;
	int			count;
}				t_cap_hit;

typedef struct s_camera
{
	t_vec3		pos;
	t_vec3		dir;
	t_vec3		up;
	t_vec3		right;
	double		fov;
	double		aspect_ratio;
	t_vec3		screen_center;
	t_vec3		horizontal;
	t_vec3		vertical;
}				t_camera;

typedef struct s_light
{
	t_vec3		pos;
	double		brightness;
	t_color		color;
}				t_light;

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
	t_color		color;
	int			checkerboard;
}				t_sphere;

typedef struct s_sphere_hit
{
	t_sphere	*sphere;
	t_ray		ray;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t1;
	double		t2;
}				t_sphere_hit;

typedef struct s_ambient
{
	double		brightness;
	t_color		color;
}				t_ambient;

typedef struct s_scene
{
	t_ambient	ambient;
	int			ambient_count;
	t_camera	camera;
	int			camera_count;
	t_light		*lights;
	int			light_count;
	t_sphere	*spheres;
	int			sphere_count;
	t_plane		*planes;
	int			plane_count;
	t_cylinder	*cylinders;
	int			cylinder_count;
	int			background_color;
	int			anti_aliasing;
}				t_scene;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int			zoom_key;
	int			camera_key;
	int			fov_key;
	t_scene		*scene;
}				t_data;

typedef struct s_light_calc
{
	double		diffuse_strength;
	double		specular_strength;
	double		shininess;
	double		spec;
}				t_light_calc;

typedef struct s_hit_record
{
	t_ray		ray;
	double		t;
	int			sphere_index;
	int			plane_index;
	int			cylinder_index;
	t_vec3		normal;
	t_vec3		hit_point;
	t_color		color;
}				t_hit_record;

typedef struct s_coord
{
	int			x;
	int			y;
	int			sx;
	int			sy;
	double		px;
	double		py;
}				t_coord;

typedef struct s_thread_data
{
	int			start_y;
	int			end_y;
	t_data		*data;
}				t_thread_data;

void			free_data(t_data *data);
// 関数宣言
// vec3.c
t_vec3			vec3(double x, double y, double z);
t_vec3			vec_add(t_vec3 a, t_vec3 b);
t_vec3			vec_sub(t_vec3 a, t_vec3 b);
t_vec3			vec_mul(t_vec3 v, double t);
double			vec_dot(t_vec3 a, t_vec3 b);
t_vec3			vec_normalize(t_vec3 v);
t_vec3			vec_scale(t_vec3 v, double s);
t_vec3			vec_cross(t_vec3 a, t_vec3 b);
t_vec3			vec_reflect(t_vec3 I, t_vec3 N);
double			vec_len2(t_vec3 v);
// ray.c
t_ray			create_ray(t_vec3 origin, t_vec3 direction);

// hit.c
int				hit_sphere(t_sphere *s, t_ray ray, double *t_hit);
int				hit_plane(t_plane *p, t_ray ray, double *t_hit);
int				hit_cylinder(t_cylinder *cy, t_ray ray, double *t_hit);

// parse.c
void			parse_rt_file(const char *filename, t_scene *scene);
void			dispatch_parse(t_scene *scene, char **tokens);
t_color			parse_color(char *str);
// render.c
void			render(t_data *data);

// utils.c
void			free_split(char **arr);
t_vec3			parse_vec3(const char *str);
double			ft_atof(char *str);
int				ft_count_words(const char *str, char delim);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isspace(int c);
void			ft_error(const char *msg);
void			ft_write(const char *str);
// key_hook.c
int				close_window(void *param);
int				keyhook(int keycode, t_data *data);
void			rotate_camera_yaw(t_camera *cam, double angle);
void			rotate_camera_pitch(t_camera *cam, double angle);
void			arrow_keys(t_data *data, int keycode);
void			move_forward(t_data *data, int keycode);
void			move_side(t_data *data, int keycode);
void			move_height(t_data *data, int keycode);
void			fov_key(t_data *data, int keycode);
// get_next_line.c
char			*get_next_line(int fd);

int				select_closest_hit(double *t_candidates, int count,
					double *t_hit);
int				check_side_hit(t_cylinder_hit *hit, double t_side);
void			calc_cylinder_quadratic(t_cylinder_hit *hit, t_quadratic *q);
int				hit_cylinder_side(t_cylinder_hit *hit);
int				check_cap_hit(t_cap_hit *info);

int				hit_cylinder(t_cylinder *cy, t_ray ray, double *t_hit);
int				hit_plane(t_plane *pl, t_ray ray, double *t_hit);
int				calc_sphere_quadratic(t_sphere_hit *hit);
int				hit_sphere(t_sphere *sphere, t_ray ray, double *t_hit);
int				hit_cylinder_caps(t_cylinder_hit *hit);

char			*ft_get_line(char *left_str);
char			*get_next_line(int fd);
char			*ft_read_to_left_str(int fd, char *left_str);
char			*ft_new_left_str(char *left_str);

char			*ft_error_read(char *buff);
char			*ft_error_join(char *left_str, char *buff);

t_vec3			vec_add(t_vec3 a, t_vec3 b);
t_vec3			vec_sub(t_vec3 a, t_vec3 b);
t_vec3			vec_mul(t_vec3 v, double t);
double			vec_dot(t_vec3 a, t_vec3 b);

t_vec3			vec_rotate(t_vec3 v, t_vec3 r, double theta);
t_vec3			vec_reflect(t_vec3 I, t_vec3 N);
t_vec3			parse_vec3(const char *str);
t_vec3			vec_normalize(t_vec3 v);

t_vec3			vec3(double x, double y, double z);
double			vec_len2(t_vec3 v);
t_vec3			vec_scale(t_vec3 v, double s);
t_vec3			vec_cross(t_vec3 a, t_vec3 b);

void			rotate_camera_yaw(t_camera *cam, double angle);
void			rotate_camera_pitch(t_camera *cam, double angle);
void			arrow_keys(t_data *data, int keycode);
void			move_forward(t_data *data, int keycode);
void			move_side(t_data *data, int keycode);

void			move_height(t_data *data, int keycode);
void			fov_key(t_data *data, int keycode);
int				keyhook(int keycode, t_data *data);
int				close_window(void *param);

void			ft_atof2(char *str, int i, double *res, double *divisor);
double			ft_atof(char *str);
void			ft_error(const char *msg);
int				ft_count_words(const char *str, char delim);

size_t			count_array(char **arr);
void			ft_write(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
void			free_split(char **arr);
int				ft_isspace(int c);

void			set_s_checker(t_sphere *s, char ***tokens);
void			sphere_check(t_sphere s);
void			new_sphere(t_scene *scene, t_sphere s);
void			parse_sphere(t_scene *scene, char ***tokens);

void			light_check(t_light light);
void			new_light(t_scene *scene, t_light light);
void			parse_light(t_scene *scene, char ***tokens);

void			parse_camera(t_scene *scene, char ***tokens);
void			camera_token(t_scene *scene, char ***tokens);

void			set_p_checker(t_plane *p, char ***tokens);
void			plane_check(t_plane plane);
void			new_plane(t_scene *scene, t_plane plane);
void			parse_plane(t_scene *scene, char ***tokens);

void			cy_check(t_cylinder cy);
void			parse_cylinder(t_scene *scene, char ***tokens);
void			new_cy(t_scene *scene, t_cylinder cy);

void			parse_ambient(t_scene *scene, char ***tokens);

t_ray			create_ray(t_vec3 origin, t_vec3 direction);
t_ray			generate_camera_ray(t_data *data, t_coord coord);
t_color			trace_ray(t_ray ray, t_data *data);

void			find_closest_intersection(t_data *data, t_hit_record *record);

void			light_set(t_color *dest, t_color src);
t_color			apply_lighting(t_hit_record record, t_light light,
					t_data *data);

void			put_pixel(t_data *data, int x, int y, t_color color);
void			render_pixel(t_data *data, t_coord coord);
void			*render_thread(void *arg);
void			render(t_data *data);

int				is_shadow_plane(t_vec3 point, t_light light, t_data *data,
					double t_hit);
int				is_shadow_sphere(t_vec3 point, t_light light, t_data *data,
					double t_hit);
int				is_shadow_cylinder(t_vec3 point, t_light light, t_data *data,
					double t_hit);
int				is_in_shadow(t_vec3 point, t_light light, t_data *data);

#endif
