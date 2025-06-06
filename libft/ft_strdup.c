/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:25:57 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/22 14:25:16 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		src_len;
	char	*t;
	char	*p;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	t = malloc((src_len + 1) * sizeof(char));
	if (t != NULL)
	{
		p = t;
		while (*src)
		{
			*p = *src;
			src++;
			p++;
		}
		*p = '\0';
	}
	return (t);
}
