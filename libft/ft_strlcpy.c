/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:26:03 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/23 18:03:20 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	len;
	unsigned int	j;

	len = 0;
	while (src[len] != '\0')
	{
		len++;
	}
	if (size == 0)
	{
		return (len);
	}
	j = 0;
	while (j < size - 1 && src[j] != '\0')
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (len);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char			src[] = "Hello, world!";
// 	char			dest[20];
// 	unsigned int	result;

// 	unsigned int size = 10; // コピーするサイズ
// 	result = ft_strlcpy(dest, src, size);
// 	printf("コピー後の文字列: %s\n", dest);
// 	printf("コピーした文字列の長さ: %u\n", result);
// 	return (0);
// }
