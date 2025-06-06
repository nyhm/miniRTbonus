/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:26:00 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/25 08:37:41 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	dest_len = 0;
	src_len = 0;
	while (dest[dest_len] != '\0' && dest_len < size)
		dest_len++;
	if (size <= dest_len)
		return (size + ft_strlen(src));
	while (src[src_len] != '\0')
		src_len++;
	i = 0;
	while (i < src_len && (dest_len + i + 1) < size)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int	main(int argc, char *argv[]) // 2つの文字列と数字１つを入力してください 入力する数字は大きく
// {
// 	if (argc != 4)
// 	{
// 		printf("2つの文字列と1つの数字を引数として入力してください。\n");
// 		return (1);
// 	}
// 	char *a = argv[1];
// 	char d[100];
// 	int i = 0;
// 	while (a[i] != '\0')
// 	{
// 		d[i] = a[i];
// 		i++;
// 	};
// 	printf("%u\n", ft_strlcat(d, argv[2], atoi(argv[3])));
// 	printf("%s\n", d);

// 	return (0);
// }