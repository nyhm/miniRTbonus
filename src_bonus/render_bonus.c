/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:47:06 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/03 06:09:49 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_color opposite_color(t_color c)
{
    t_color opp;
    opp.r = 255 - c.r;
    opp.g = 255 - c.g;
    opp.b = 255 - c.b;
    return opp;
}

int is_cylinder_bottom_checkerboard(t_vec3 point, t_cylinder *cy, double scale)
{
    // 円柱軸方向（正規化済み）
    t_vec3 axis = cy->direction;

    // 底面の中心点（cy->center - axis * (height / 2) とかなら高さ半分下が底面中心）
    // ここでは仮に cy->center が底面中心だとします
    t_vec3 bottom_center = cy->center;

    // 底面平面におけるpointの2D座標を取得
    t_vec3 diff = vec_sub(point, bottom_center);

    // 底面の平面を定義するために軸方向に垂直な2つのベクトル（u, v）を作る
    // 例えば u = vec_cross(axis, (0,1,0)) など（軸がy方向でなければ別の方法も）
    t_vec3 world_up = (t_vec3){0,1,0};
    t_vec3 u = vec_normalize(vec_cross(axis, world_up));
    if (vec_len2(u) < 0.001)  // axis と world_up がほぼ平行なら別のベクトル使う
        u = (t_vec3){1,0,0};
    t_vec3 v = vec_cross(axis, u);

    // diff を (u, v) ベクトルに投影して2D座標に変換
    double x_2d = vec_dot(diff, u) * scale;
    double y_2d = vec_dot(diff, v) * scale;

    int checker_x = (int)floor(x_2d);
    int checker_y = (int)floor(y_2d);

    return (checker_x + checker_y) % 2 == 0;
}

int is_cylinder_checkerboard(t_vec3 point, t_cylinder *cy, double scale_height, double scale_angle, double scale_bottom)
{
    // 軸方向
    t_vec3 axis = cy->direction;
    t_vec3 cp = vec_sub(point, cy->center);

    // 高さ成分
    double height = vec_dot(cp, axis);

    if (height < 0.001) { // 底面近くなら底面のチェッカー判定を使う
        return is_cylinder_bottom_checkerboard(point, cy, scale_bottom);
    } else {
        // 側面の計算
        double scaled_height = height * scale_height;

        t_vec3 radial = vec_sub(cp, vec_mul(axis, height));
        double angle = atan2(radial.z, radial.x) * scale_angle;

        int checker_x = (int)floor(scaled_height);
        int checker_y = (int)floor(angle);

        return (checker_x + checker_y) % 2 == 0;
    }
}


// 円柱チェッカーの色を取得
t_color get_cylinder_checker_color(t_vec3 point, t_cylinder *cy, double scale_height, double scale_angle,double scale_bottom, t_color c1, t_color c2)
{
    if (is_cylinder_checkerboard(point, cy, scale_height, scale_angle, scale_bottom))
        return c1;
    else
        return c2;
}

int is_checkerboard_z(t_vec3 point, double scale)
{
    
    int y = (int)floor(point.y * scale);
    int x = (int)floor(point.x * scale);
    return (y + x) % 2 == 0;
}

// チェッカーボードの色を取得
t_color get_checkerboard_color_z(t_vec3 point, double scale, t_color c1, t_color c2)
{
    if (is_checkerboard_z(point, scale))
        return c1;
    else
        return c2;
}

int is_checkerboard_x(t_vec3 point, double scale)
{
    
    int y = (int)floor(point.y * scale);
    int z = (int)floor(point.z * scale);
    return (y + z) % 2 == 0;
}

// チェッカーボードの色を取得
t_color get_checkerboard_color_x(t_vec3 point, double scale, t_color c1, t_color c2)
{
    if (is_checkerboard_x(point, scale))
        return c1;
    else
        return c2;
}
// チェッカーボード判定
int is_checkerboard_y(t_vec3 point, double scale)
{
    
    int x = (int)floor(point.x * scale);
    int z = (int)floor(point.z * scale);
    return (x + z) % 2 == 0;
}

// チェッカーボードの色を取得
t_color get_checkerboard_color_y(t_vec3 point, double scale, t_color c1, t_color c2)
{
    if (is_checkerboard_y(point, scale))
        return c1;
    else
        return c2;
}

t_color get_sphere_checker_color(t_vec3 point, t_vec3 center, double radius, double scale, t_color c1, t_color c2)
{
    t_vec3 p_centered = vec_sub(point, center);

    double theta = atan2(p_centered.z, p_centered.x);
    if (theta < 0) theta += 2 * M_PI;
    double phi = acos(p_centered.y / radius);

    int check_u = (int)(theta * scale);
    int check_v = (int)(phi * scale);

    if ((check_u + check_v) % 2 == 0)
        return c1;
    else
        return c2;
}


void put_pixel(t_data *data, int x, int y, t_color color)
{
    char *dst;
    int pixel;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;

    pixel = (color.r << 16) | (color.g << 8) | (color.b);
    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int *)dst = pixel;
}

void find_closest_plane(t_ray ray, t_data *data, t_color *color, t_hit_record *record)
{
    int i = 0;
    while( i < data->scene->plane_count)
    {
        double t_hit = 0.0;
        if (hit_plane(&data->scene->planes[i], ray, &t_hit)
            && t_hit < record->t && t_hit > 0.001)
        {
            t_plane *pl = &data->scene->planes[i];
            record->t = t_hit;
            record->plane_index = i;
            record->sphere_index = -1;
            record->cylinder_index = -1;

            t_vec3 hit_point = vec_add(ray.origin, vec_mul(ray.direction, t_hit));
            t_color base = pl->color;
            t_color alt = opposite_color(base);
            record->hit_point = hit_point;
            record->normal = pl->normal;
            if (pl->normal.y != 0 && pl->checkerboard)
                *color = get_checkerboard_color_y(hit_point, 0.5, base, alt);
            else if (pl->normal.x != 0 && pl->checkerboard)
                *color = get_checkerboard_color_x(hit_point, 0.5, base, alt);
            else if (pl->normal.z != 0 && pl->checkerboard)
                *color = get_checkerboard_color_z(hit_point, 0.5, base, alt);
            else
                *color = base;
        }
        i++;
    }
}


void find_closest_sphere(t_ray ray, t_data *data, t_color *color,t_hit_record *record)
{
    int i = 0;
    while ( i < data->scene->sphere_count)
    {
        double t_hit=0.0;
        if (hit_sphere(&data->scene->spheres[i], ray, &t_hit)
            && t_hit < record->t && t_hit > 0.001)
        {
            record->t = t_hit;
            *color = data->scene->spheres[i].color;
            record->sphere_index = i;
            record->plane_index = -1;
            record->cylinder_index = -1;
            // ヒット地点の座標を計算
            t_vec3 hit_point = vec_add(ray.origin, vec_mul(ray.direction, t_hit));
            // 法線 = ヒット地点 - 球の中心（正規化する）
            t_vec3 normal = vec_normalize(vec_sub(hit_point, data->scene->spheres[i].center));

            // 法線を record に保存（t_hit_recordにnormalがあると仮定）
            record->normal = normal;
            record->hit_point = hit_point;
            // チェッカーボード色を計算
            if(data->scene->spheres[i].checkerboard)
                *color = get_sphere_checker_color(hit_point, data->scene->spheres[i].center,
                                              data->scene->spheres[i].radius, 3.0,
                                              data->scene->spheres[i].color, opposite_color(data->scene->spheres[i].color));
        }
        i++;
    }
}

void find_closest_cylinder(t_ray ray, t_data *data, t_color *color,t_hit_record *record)
{int i = 0;
    while( i < data->scene->cylinder_count)
    {
        double t_hit=0.0;
        if (hit_cylinder(&data->scene->cylinders[i], ray, &t_hit)
            && t_hit < record->t && t_hit > 0.001)
        {
            record->t = t_hit;
            *color = data->scene->cylinders[i].color;
            record->cylinder_index = i;
            record->sphere_index = -1;
            record->plane_index = -1;
            // ヒット地点の座標を計算
            t_vec3 hit_point = vec_add(ray.origin, vec_mul(ray.direction, t_hit));
            t_cylinder *cy = &data->scene->cylinders[i];

            // ヒット地点とシリンダー中心ベクトル
            t_vec3 cp = vec_sub(hit_point, cy->center);

            // cp をシリンダー軸方向に投影
            double proj = vec_dot(cp, cy->direction);

            // 法線は cp から軸方向成分を引いたベクトルを正規化したもの
            t_vec3 normal = vec_normalize(vec_sub(cp, vec_mul(cy->direction, proj)));

            // record に法線を保存
            record->normal = normal;
            record->hit_point = hit_point;
            // チェッカーボード色を計算
            if(data->scene->cylinders[i].checkerboard)
                *color = get_cylinder_checker_color(hit_point, &data->scene->cylinders[i], 1.0, 10.0,1.0,
                                                data->scene->cylinders[i].color, opposite_color(data->scene->cylinders[i].color));
        }
        i++;
    }
}

void find_closest_intersection(t_ray ray, t_data *data, t_color *color,t_hit_record *record)
{
    
    find_closest_plane(ray, data, color,record);
    find_closest_sphere(ray, data, color,record);
    find_closest_cylinder(ray, data, color,record);
}

int is_shadow_plane(t_vec3 point,t_light light,t_data *data, double t_hit)
{
    t_vec3 light_dir = vec_normalize(vec_sub(light.pos, point));
    double light_distance = vec_len2(vec_sub(light.pos, point));
    t_ray shadow_ray = { .origin = vec_add(point, vec_mul(light_dir, 1e-4)), // 少しオフセット
                         .direction = light_dir };
    int i = 0;
    while( i < data->scene->plane_count)
    {
        if (hit_plane(&data->scene->planes[i], shadow_ray, &t_hit) && t_hit > 0.001 && t_hit*t_hit < light_distance)
            return(1);
        i++;
    }
    return (0);
}

int is_shadow_sphere(t_vec3 point, t_light light, t_data *data, double t_hit)
{
    t_vec3 light_dir = vec_normalize(vec_sub(light.pos, point));
    double light_distance = vec_len2(vec_sub(light.pos, point));
    t_ray shadow_ray = { .origin = vec_add(point, vec_mul(light_dir, 1e-4)), // 少しオフセット
                         .direction = light_dir };
    int i = 0;
    while( i < data->scene->sphere_count)
    {
        if (hit_sphere(&data->scene->spheres[i], shadow_ray, &t_hit) && t_hit > 0.001 && t_hit*t_hit < light_distance)
            return (1);
        i++;
    }
    return (0);
}

int is_shadow_cylinder(t_vec3 point, t_light light, t_data *data, double t_hit)
{
    t_vec3 light_dir = vec_normalize(vec_sub(light.pos, point));
    double light_distance = vec_len2(vec_sub(light.pos, point));
    t_ray shadow_ray = { .origin = vec_add(point, vec_mul(light_dir, 1e-4)), // 少しオフセット
                         .direction = light_dir };
    int i = 0;
    while( i < data->scene->cylinder_count)
    {
        if (hit_cylinder(&data->scene->cylinders[i], shadow_ray, &t_hit) && t_hit > 0.001 && t_hit*t_hit < light_distance)
            return (1); 
        i++;
    }
    return (0);
}

int is_in_shadow(t_vec3 point, t_light light, t_data *data)
{
    double t_hit=0.0;
    int shadowed = 0;
    shadowed = is_shadow_plane(point, light, data, t_hit);
    shadowed |= is_shadow_sphere(point, light, data, t_hit);
    shadowed |= is_shadow_cylinder(point, light, data, t_hit);
    return (shadowed);
}
t_color apply_lighting(t_color base, t_vec3 hit_point, t_vec3 normal, t_light light, t_data *data)
{
    t_vec3 light_dir = vec_normalize(vec_sub(light.pos, hit_point));
    t_vec3 view_dir = vec_normalize(vec_sub(data->scene->camera.pos, hit_point));

    double ambient_strength = data->scene->ambient.brightness;
    double diffuse_strength = 0.0;
    double specular_strength = 0.5;
    double shininess = 64.0;

    // === 環境光 ===
    double r = base.r * ambient_strength * light.color.r / 255.0;
    double g = base.g * ambient_strength * light.color.g / 255.0;
    double b = base.b * ambient_strength * light.color.b / 255.0;

    // === シャドウ判定 ===
    if (!is_in_shadow(hit_point, light, data))
    {
        // === 拡散反射 ===
        diffuse_strength = fmax(vec_dot(normal, light_dir), 0.0);

        // === 鏡面反射 ===
        t_vec3 reflect_dir = vec_reflect(vec_mul(light_dir, -1), normal);
        double spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), shininess);

        // === 合成 ===
        r += base.r * diffuse_strength * light.brightness * light.color.r / 255.0;
        g += base.g * diffuse_strength * light.brightness * light.color.g / 255.0;
        b += base.b * diffuse_strength * light.brightness * light.color.b / 255.0;

        r += specular_strength * spec * light.color.r;
        g += specular_strength * spec * light.color.g;
        b += specular_strength * spec * light.color.b;
    }

    // === 範囲制限 ===
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;

    return (t_color){(int)r, (int)g, (int)b};
}


t_color trace_ray(t_ray ray, t_data *data)
{
    t_color final = {0, 0, 0}; // 初期は黒
    t_color base = (t_color){100, 100, 100}; // 物体の元の色（これは本来マテリアル側から来るべき）
    t_hit_record record = {
        .t = INFINITY,
        .sphere_index = -1,
        .plane_index = -1,
        .cylinder_index = -1,
        .normal = {0, 0, 0} // 初期化
    };
    find_closest_intersection(ray, data, &base,&record);

    if (record.t < INFINITY)
    {
        int i = 0;
        while ( i < data->scene->light_count)
        {
            t_light light = data->scene->lights[i];
            t_color light_result = apply_lighting(base, record.hit_point, record.normal, light, data);
            final.r += light_result.r;
            final.g += light_result.g;
            final.b += light_result.b;
            i++;
        }


        if (final.r > 255) final.r = 255;
        if (final.g > 255) final.g = 255;
        if (final.b > 255) final.b = 255;
    } else {
        // ヒットしなかったら背景色（ここではbase）
        final = base;
    }

    return final;
}

t_ray generate_camera_ray(t_data *data, int x, int y, int sx, int sy)
{
    double u = (x + (sx + 0.5) / SAMPLES) / WIDTH;
    double v = (y + (sy + 0.5) / SAMPLES) / HEIGHT;

    double scale = tan(data->scene->camera.fov * 0.5 * M_PI / 180.0);
    double px = (2 * u - 1) * data->scene->camera.aspect_ratio * scale;
    double py = (1 - 2 * v) * scale;

    t_vec3 dir = vec_normalize(vec_add(
        vec_add(
            vec_mul(data->scene->camera.right, px),
            vec_mul(data->scene->camera.up, py)
        ),
        data->scene->camera.dir
    ));

    return create_ray(data->scene->camera.pos, dir);
}


void render_pixel(t_data *data,int x,int y)
{
    int r = 0;
    int g = 0;
    int b = 0;
    r = 0;
    g = 0;
    b = 0;

    int sy = 0;
    while ( sy < SAMPLES) {
        int sx = 0;
        while ( sx < SAMPLES)
        {
            t_ray ray = generate_camera_ray(data, x, y, sx, sy);
            t_color sample = trace_ray(ray, data);
            r += sample.r;
            g += sample.g;
            b += sample.b;
            sx++;
        }
        sy++;
    }

    t_color final_color = {
        r / (SAMPLES * SAMPLES),
        g / (SAMPLES * SAMPLES),
        b / (SAMPLES * SAMPLES)
    };

    put_pixel(data, x, y, final_color);
}

void *render_thread(void *arg)
{
    t_thread_data *td = (t_thread_data *)arg;
    int x;
    int y;
    y = td->start_y; 
    while(y < td->end_y) {
        x = 0;
        while( x < WIDTH)
        {
            render_pixel(td->data, x, y);
            x++;
        }
        y++;
    }
    return NULL;
}


void render(t_data *data)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    pthread_t threads[NUM_THREADS];
    t_thread_data thread_data[NUM_THREADS];
    int slice = HEIGHT / NUM_THREADS;
    int i = 0;
    while( i < NUM_THREADS)
    {
        thread_data[i].start_y = i * slice;
        thread_data[i].end_y = (i == NUM_THREADS - 1) ? HEIGHT : (i + 1) * slice;
        thread_data[i].data = data;
        pthread_create(&threads[i], NULL, render_thread, &thread_data[i]);
        i++;
    }
    i=0;
    while(i < NUM_THREADS)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    gettimeofday(&end, NULL);
    double elapsed_time = (end.tv_sec - start.tv_sec) +
                        (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Elapsed time: %.3f seconds\n", elapsed_time);
}


// void render(t_data *data)//pthreadを使わないバージョン
// {
    
//     int x;
//     int y;
//     struct timeval start, end;
//     gettimeofday(&start, NULL);
    
//     y = 0;
//     while( y < HEIGHT)
//     {
//         x = 0; 
//         while(x < WIDTH)
//         {
//             render_pixel(data, x, y);
//             x++;
//         }
//         y++;
//     }
    
//     gettimeofday(&end, NULL);
//     double elapsed_time = (end.tv_sec - start.tv_sec) +
//                         (end.tv_usec - start.tv_usec) / 1000000.0;
//     printf("Elapsed time: %.3f seconds\n", elapsed_time);
// }

