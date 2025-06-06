/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:46:25 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/02 17:03:37 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_ray create_ray(t_vec3 origin, t_vec3 direction)
{
    t_ray r;
    r.origin = origin;
    r.direction = direction;
    return r;
}
