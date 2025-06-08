/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 23:33:56 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 15:51:00 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

int	is_unit_vector(t_vec3 vec3);

int	is_unit_vector(t_vec3 vec3)
{
	double	length;

	length = sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);
	return (fabs(length - 1.0) < 1e-6);
}
