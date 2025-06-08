/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 23:20:41 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 23:25:22 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	is_unit_vector(t_vec3 vec3)
{
	double	length;

	length = sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);
	return (fabs(length - 1.0) < 1e-6);
}
