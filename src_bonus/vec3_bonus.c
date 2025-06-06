/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:45:50 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/02 17:03:53 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vec3 vec3(double x, double y, double z) { return (t_vec3){x, y, z}; }

t_vec3 vec_add(t_vec3 a, t_vec3 b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); } //ベクトルの加算
t_vec3 vec_sub(t_vec3 a, t_vec3 b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); } //ベクトルの減算
t_vec3 vec_mul(t_vec3 v, double t) { return vec3(v.x * t, v.y * t, v.z * t); } //ベクトルのスカラー倍
double vec_dot(t_vec3 a, t_vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; } //ベクトルの内積
t_vec3 vec_reflect(t_vec3 I, t_vec3 N)
{
    return vec_sub(I, vec_mul(N, 2.0 * vec_dot(I, N)));
}

double vec_len2(t_vec3 v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}
t_vec3 vec_scale(t_vec3 v, double s)
{
    t_vec3 result;
    result.x = v.x * s;
    result.y = v.y * s;
    result.z = v.z * s;
    return result;
}

t_vec3 vec_cross(t_vec3 a, t_vec3 b)
{
    t_vec3 res;
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
    return res;
}


t_vec3 parse_vec3(const char *str)
{
    t_vec3 vec;
    char **parts = ft_split(str, ',');
    if (!parts || ft_count_words(str, ',') != 3)
        return (t_vec3){0, 0, 0};
    vec.x = ft_atof(parts[0]);
    vec.y = ft_atof(parts[1]);
    vec.z = ft_atof(parts[2]);
    free_split(parts);
    return vec;
} //文字列からt_vec3構造体を生成する関数

t_vec3 vec_normalize(t_vec3 v)
{
    double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);//３次元の２乗和平方根->３次元の長さ
    t_vec3 result;

    if (length == 0.0)
        return (t_vec3){0, 0, 0}; // 長さ0はそのまま返す（必要に応じて処理変更可）

    result.x = v.x / length;
    result.y = v.y / length;
    result.z = v.z / length;
    //長さで割ることで、ベクトルの大きさを1にする
    return result;
}
