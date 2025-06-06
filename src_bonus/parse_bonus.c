/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:03 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/06 22:55:46 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"
#include <stdio.h>
#include <string.h>

t_color parse_color(char *str)
{
    t_color color = {0, 0, 0};
    char **rgb_tokens = ft_split(str, ',');
    if (!rgb_tokens)
        return color;
    color.r = ft_atoi(rgb_tokens[0]);
    color.g = ft_atoi(rgb_tokens[1]);
    color.b = ft_atoi(rgb_tokens[2]);
    if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255 || color.b < 0 || color.b > 255) {
        free_split(rgb_tokens);
        ft_error("Error: color values must be between 0 and 255");
    }
    free_split(rgb_tokens);
    return color;
}
void parse_plane(t_scene *scene, char ***tokens)
{
    size_t count_tokens = count_array(tokens[0]);
    char **t = *tokens;

    if (count_tokens < 4 || ft_isspace(t[1][0]) || ft_isspace(t[2][0]) || ft_isspace(t[3][0]))
        ft_error("Error: invalid plane line\n");

    t_plane plane;
    plane.point = parse_vec3(t[1]);
    plane.normal = vec_normalize(parse_vec3(t[2]));
    plane.color = parse_color(t[3]);

    if (vec_len2(plane.normal) == 0)
        ft_error("Error: plane normal cannot be zero vector\n");

    if (plane.point.x < -1000 || plane.point.x > 1000 ||
        plane.point.y < -1000 || plane.point.y > 1000 ||
        plane.point.z < -1000 || plane.point.z > 1000)
        ft_error("Error: plane point coordinates must be between -1000 and 1000\n");

    size_t new_count = scene->plane_count + 1;
    t_plane *new_arr = malloc(sizeof(t_plane) * new_count);
    if (!new_arr)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ft_memset(new_arr, 0, sizeof(t_plane) * new_count); // 新しい配列を初期化
    if (scene->planes)
    {
        ft_memcpy(new_arr, scene->planes, sizeof(t_plane) * scene->plane_count);
        free(scene->planes);
    }

    if (t[4] && (ft_strcmp(t[4], "checkerboard") == 0 || ft_strcmp(t[4], "checkerboard\n") == 0))
    {
        plane.checkerboard = 1;
        (*tokens )+= 5;  // 5つ分進める（P + point + normal + color + checkerboard）
    }
    else
    {
        plane.checkerboard = 0;
        (*tokens )+= 4;  // 4つ分進める（P + point + normal + color）
    }

    new_arr[scene->plane_count] = plane;
    scene->planes = new_arr;
    scene->plane_count = new_count;
}


void parse_cylinder(t_scene *scene, char ***tokens)
{
    size_t count_tokens = count_array(tokens[0]);
    char **t = *tokens;

    if (count_tokens < 6||
        ft_isspace(t[1][0]) || ft_isspace(t[2][0]) || ft_isspace(t[3][0]) || ft_isspace(t[4][0]) || ft_isspace(t[5][0]))
        ft_error("Error: invalid cylinder line\n");

    t_cylinder cy;
    cy.center = parse_vec3(t[1]);
    cy.direction = vec_normalize(parse_vec3(t[2]));
    cy.radius = atof(t[3]) / 2.0;
    cy.height = atof(t[4]);
    cy.color = parse_color(t[5]);

    size_t new_count = scene->cylinder_count + 1;
    t_cylinder *new_arr = malloc(sizeof(t_cylinder) * new_count);
    if (!new_arr) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ft_memset(new_arr, 0, sizeof(t_cylinder) * new_count); // 新しい配列を初期化
    if (scene->cylinders) {
        ft_memcpy(new_arr, scene->cylinders, sizeof(t_cylinder) * scene->cylinder_count);
        free(scene->cylinders);
    }

    if (vec_len2(cy.direction) == 0) {
        free(new_arr);
        ft_error("Error: cylinder direction cannot be zero vector\n");
    }
    if (cy.center.x < -1000 || cy.center.x > 1000 ||
        cy.center.y < -1000 || cy.center.y > 1000 ||
        cy.center.z < -1000 || cy.center.z > 1000)
        ft_error("Error: cylinder center coordinates must be between -1000 and 1000\n");
    if (cy.radius <= 0)
        ft_error("Error: cylinder radius must be greater than 0\n");
    if (cy.height <= 0)
        ft_error("Error: cylinder height must be greater than 0\n");

    if (t[6] && (ft_strcmp(t[6], "checkerboard") == 0 || ft_strcmp(t[6], "checkerboard\n") == 0)) {
        cy.checkerboard = 1;
        (*tokens) += 7;  // 7つ分進める (C + center + direction + radius + height + color + checkerboard)
    } else {
        cy.checkerboard = 0;
        (*tokens) += 6;  // 6つ分進める (C + center + direction + radius + height + color)
    }

    new_arr[scene->cylinder_count] = cy;
    scene->cylinders = new_arr;
    scene->cylinder_count = new_count;
}



static void parse_camera(t_scene *scene, char ***tokens)
{
    size_t count_tokens = count_array(tokens[0]);
    if (count_tokens < 4 ||
        ft_isspace((*tokens)[1][0]) || ft_isspace((*tokens)[2][0]) || ft_isspace((*tokens)[3][0]))
        ft_error("Error: invalid camera line\n");
    
    scene->camera.pos = parse_vec3((*tokens)[1]);
    scene->camera.dir = vec_normalize(parse_vec3((*tokens)[2]));
    scene->camera.fov = ft_atof((*tokens)[3]);
    if (vec_len2(scene->camera.dir) == 0) 
        ft_error("Error: camera direction cannot be zero vector\n");
    if (scene->camera.fov <= 0 || scene->camera.fov >= 180)
        ft_error("Error: camera FOV must be between 0 and 180 degrees\n");

    scene->camera.aspect_ratio = (double)WIDTH / HEIGHT;
    t_vec3 world_up = {0, 1, 0};
    if (fabs(vec_dot(scene->camera.dir, world_up)) > 0.999)
        world_up = (t_vec3){0, 0, 1};
    
    scene->camera.right = vec_normalize(vec_cross(scene->camera.dir, world_up));
    scene->camera.up = vec_cross(scene->camera.right, scene->camera.dir);
    scene->camera.screen_center = vec_add(scene->camera.pos, vec_scale(scene->camera.dir, 1.0));

    double theta = scene->camera.fov * M_PI / 180.0;
    double half_height = tan(theta / 2);
    double half_width = scene->camera.aspect_ratio * half_height;

    scene->camera.horizontal = vec_scale(scene->camera.right, half_width * 2);
    scene->camera.vertical = vec_scale(scene->camera.up, half_height * 2);

    (*tokens) += 4; // ずらす
}

static void parse_light(t_scene *scene, char ***tokens)
{
    size_t count_tokens = count_array(tokens[0]);
    if (count_tokens < 4 ||
        ft_isspace((*tokens)[1][0]) || ft_isspace((*tokens)[2][0]) || ft_isspace((*tokens)[3][0]))
        ft_error("Error: invalid light line\n");

    t_light light;
    light.pos = parse_vec3((*tokens)[1]);
    light.brightness = ft_atof((*tokens)[2]);
    light.color = parse_color((*tokens)[3]);

    if (light.brightness < 0 || light.brightness > 1)
        ft_error("Error: light brightness must be between 0 and 1\n");

    if (light.pos.x < -1000 || light.pos.x > 1000 ||
        light.pos.y < -1000 || light.pos.y > 1000 ||
        light.pos.z < -1000 || light.pos.z > 1000)
        ft_error("Error: light position coordinates must be between -1000 and 1000\n");

    if (light.color.r < 0 || light.color.r > 255 ||
        light.color.g < 0 || light.color.g > 255 ||
        light.color.b < 0 || light.color.b > 255)
        ft_error("Error: light color values must be between 0 and 255\n");

    size_t new_count = scene->light_count + 1;
    t_light *new_arr = malloc(sizeof(t_light) * new_count);
    if (!new_arr)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ft_memset(new_arr, 0, sizeof(t_light) * new_count); // 新しい配列を初期化   
    if (scene->lights)
    {
        ft_memcpy(new_arr, scene->lights, sizeof(t_light) * scene->light_count);
        free(scene->lights);
    }

    new_arr[scene->light_count] = light;
    scene->lights = new_arr;
    scene->light_count = new_count;

    (*tokens) += 4;  // 呼び出し元のポインタも4つ進める
}


static void parse_sphere(t_scene *scene, char ***tokens)
{
    size_t count_tokens = count_array(tokens[0]);
    char **t = *tokens;

    if (count_tokens < 4|| ft_isspace(t[1][0]) || ft_isspace(t[2][0]) || ft_isspace(t[3][0]))
        ft_error("Error: invalid sphere line\n");

    t_sphere s;
    s.center = parse_vec3(t[1]);
    s.radius = ft_atof(t[2]) / 2.0;
    s.color  = parse_color(t[3]);

    if (s.radius <= 0)
        ft_error("Error: sphere radius must be greater than 0\n");

    if (s.center.x < -1000 || s.center.x > 1000 ||
        s.center.y < -1000 || s.center.y > 1000 ||
        s.center.z < -1000 || s.center.z > 1000)
        ft_error("Error: sphere center coordinates must be between -1000 and 1000\n");

    if (s.color.r < 0 || s.color.r > 255 ||
        s.color.g < 0 || s.color.g > 255 ||
        s.color.b < 0 || s.color.b > 255)
        ft_error("Error: sphere color values must be between 0 and 255\n");

    size_t new_count = scene->sphere_count + 1;
    t_sphere *new_arr = malloc(sizeof(t_sphere) * new_count);
    if (!new_arr)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ft_memset(new_arr, 0, sizeof(t_sphere) * new_count); // 新しい配列を初期化
    if (scene->spheres)
    {
        ft_memcpy(new_arr, scene->spheres, sizeof(t_sphere) * scene->sphere_count);
        free(scene->spheres);
    }

    if (t[4] && (ft_strcmp(t[4], "checkerboard") == 0 || ft_strcmp(t[4], "checkerboard\n") == 0))
    {
        s.checkerboard = 1;
        *tokens += 5;  // 5つ分進める（C + center + radius + color + checkerboard）
    }
    else
    {
        s.checkerboard = 0;
        *tokens += 4;  // 4つ分進める（C + center + radius + color）
    }

    new_arr[scene->sphere_count] = s;
    scene->spheres = new_arr;
    scene->sphere_count = new_count;
}


void parse_ambient(t_scene *scene, char ***tokens)
{
    size_t count_tokens = count_array(tokens[0]);
    if (count_tokens < 3|| ft_isspace((*tokens)[1][0]) || ft_isspace((*tokens)[2][0]))
        ft_error("Error: invalid ambient line\n");
    
    scene->ambient.brightness = ft_atof((*tokens)[1]);
    scene->ambient.color = parse_color((*tokens)[2]);
    
    (*tokens) += 3;  // ここで呼び出し元のポインタも3つ分進む
}


int is_empty_or_comment(char *line)
{
    int i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    if (line[i] == '\0')
        return 1;
    if (line[i] == '#')
        return 1;
    if (line[i] == '\n')
        return 1;
    return 0;
}


void dispatch_parse(t_scene *scene, char **tokens)//もう少し厳しくすべき
{
    
    while (*tokens) {
        if (ft_strcmp(tokens[0], "A") == 0) 
            parse_ambient(scene, &tokens);
        else if (ft_strcmp(tokens[0], "C") == 0)
            parse_camera(scene, &tokens);
        else if (ft_strcmp(tokens[0], "L") == 0)
            parse_light(scene, &tokens);
        else if (ft_strcmp(tokens[0], "sp") == 0)
            parse_sphere(scene, &tokens);
        else if (ft_strcmp(tokens[0], "pl") == 0)
            parse_plane(scene, &tokens);
        else if (ft_strcmp(tokens[0], "cy") == 0)
            parse_cylinder(scene, &tokens);
        else
            tokens++;  // 次のトークンへ
    }
}


void parse_line(char *line, t_scene *scene)
{
    char **tokens;

    if (is_empty_or_comment(line))
        return;
    tokens = ft_split(line, ' ');
    if (!tokens || !tokens[0])
    {
        free_split(tokens);
        return;
    }
    dispatch_parse(scene, tokens);

    free_split(tokens);
}


void parse_rt_file(const char *filename, t_scene *scene)
{
	int		fd;
	char	*line;
    int has_read = 0;

	fd = open(filename, O_RDONLY);
	if (fd < 0){
		perror("Error opening file");
        exit(EXIT_FAILURE);
    }
	while ((line = get_next_line(fd)) != NULL)
	{
        has_read = 1;
		parse_line(line, scene);
		free(line);
	}
	close(fd);
    if(!has_read)
        ft_error("Error: file is empty or not readable\n");
}
