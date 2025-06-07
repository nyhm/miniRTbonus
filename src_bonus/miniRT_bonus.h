/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:59:18 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 20:12:56 by hnagashi         ###   ########.fr       */
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

typedef struct s_cy_coord
{
	double		height;
	double		angle;
}				t_cy_coord;

typedef struct s_cy_checkerboard_scale
{
	double		height;
	double		angle;
	double		bottom;
}				t_cy_checkerboard_scale;

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

// get_next_line_bonus.c
char			*get_next_line(int fd);

// get_next_line_utils_bonus.c
char			*ft_error_read(char *buff);
char			*ft_error_join(char *left_str, char *buff);

// hit_bonus.c
int				hit_sphere(t_sphere *sphere, t_ray ray, double *t_hit);
int				hit_cylinder(t_cylinder *cy, t_ray ray, double *t_hit);
int				hit_plane(t_plane *pl, t_ray ray, double *t_hit);

// hit_cylinder_bonus.c
int				select_closest_hit(double *t_candidates, int count,
					double *t_hit);
int				hit_cylinder_side(t_cylinder_hit *hit);
int				check_cap_hit(t_cap_hit *info);

// key_hook_bonus.c
int				keyhook(int keycode, t_data *data);
int				close_window(void *param);

// key_hook_utils_bonus.c
void			arrow_keys(t_data *data, int keycode);
void			move_forward(t_data *data, int keycode);
void			move_side(t_data *data, int keycode);

// parse_ambient.c
void			parse_ambient(t_scene *scene, char ***tokens);

// parse_bonus.c
void			parse_rt_file(const char *filename, t_scene *scene);
t_color			parse_color(char *str);

// parse_camera_bonus.c
void			parse_camera(t_scene *scene, char ***tokens);

// parse_cylinder_bonus.c
void			cy_check(t_cylinder cy);
void			parse_cylinder(t_scene *scene, char ***tokens);

// parse_light_bonus.c
void			light_check(t_light light);
void			parse_light(t_scene *scene, char ***tokens);

// parse_plane_bonus.c
void			set_p_checker(t_plane *p, char ***tokens);
void			parse_plane(t_scene *scene, char ***tokens);

// parse_sphere_bonus.c
void			set_s_checker(t_sphere *s, char ***tokens);
void			parse_sphere(t_scene *scene, char ***tokens);

// checker_bonus.c
t_color			opposite_color(t_color c);
t_color			get_checkerboard_color(t_hit_record *record, t_plane *pl,
					double scale);
t_color			get_sphere_checker_color(t_hit_record *record, t_sphere *s,
					double scale);

// checker_cy_bonus.c
t_color			get_cylinder_checker_color(t_vec3 point, t_cylinder *cy);

// find_bonus.c
void			find_closest_plane(t_data *data, t_hit_record *record);
void			find_closest_sphere(t_data *data, t_hit_record *record);
void			find_closest_cylinder(t_data *data, t_hit_record *record);

// light_bonus.c
void			light_set(t_color *dest, t_color src);
t_color			apply_lighting(t_hit_record record, t_light light,
					t_data *data);

// ray_bonus.c
t_ray			create_ray(t_vec3 origin, t_vec3 direction);
t_ray			generate_camera_ray(t_data *data, t_coord coord);
t_color			trace_ray(t_ray ray, t_data *data);

// render_bonus.c

void			render(t_data *data);

// shadow_bonus.c
int				is_in_shadow(t_vec3 point, t_light light, t_data *data);

// utils_bonus.c
size_t			count_array(char **arr);
void			ft_write(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
void			free_split(char **arr);
int				ft_isspace(int c);

// utils2_bonus.c
void			ft_atof2(char *str, int i, double *res, double *divisor);
double			ft_atof(char *str);
void			ft_error(const char *msg);
int				ft_count_words(const char *str, char delim);

// utils3.c
t_color			color_scale(t_color color, double scale);
t_color			color_mul(t_color a, t_color b);
void			find_closest_intersection(t_data *data, t_hit_record *record);

// vec3_basic_bonus.c
t_vec3			vec_add(t_vec3 a, t_vec3 b);
t_vec3			vec_sub(t_vec3 a, t_vec3 b);
t_vec3			vec_mul(t_vec3 v, double t);
double			vec_dot(t_vec3 a, t_vec3 b);

// vec3_bonus.c
t_vec3			vec_rotate(t_vec3 v, t_vec3 r, double theta);
t_vec3			vec_reflect(t_vec3 I, t_vec3 N);
t_vec3			parse_vec3(const char *str);
t_vec3			vec_normalize(t_vec3 v);

// vec3_utils_bonus.c
t_vec3			vec3(double x, double y, double z);
double			vec_len2(t_vec3 v);
t_vec3			vec_scale(t_vec3 v, double s);
t_vec3			vec_cross(t_vec3 a, t_vec3 b);

// main_bonus.c
void			free_data(t_data *data);
#endif
