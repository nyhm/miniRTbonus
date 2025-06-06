/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:25:18 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/23 19:54:16 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr++ = 0;
	}
}

// #include <stdio.h>
// #include <string.h> // memset と memcmp 用
// #include <strings.h> // bzero 用

// int	main(void)
// {
// 	char	buffer[10];
// 	char	buffer2[10];
// 	char	expected[10] = {0};

// 	ft_bzero(buffer, 10);
// 	bzero(buffer2, 10);
// 	// memcmp で比較して正しくゼロ埋めされているか確認
// 	if (memcmp(buffer, expected, 10) == 0)
// 	{
// 		printf("bzero successful: All bytes are zero.\n");
// 	}
// 	else
// 	{
// 		printf("bzero failed: Some bytes are not zero.\n");
// 	}
// 	if (memcmp(buffer2, expected, 10) == 0)
// 	{
// 		printf("bzero successful: All bytes are zero.\n");
// 	}
// 	else
// 	{
// 		printf("bzero failed: Some bytes are not zero.\n");
// 	}
// 	return (0);
// }
