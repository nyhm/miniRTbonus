/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:25:41 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/23 23:00:00 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr = s;
	unsigned char		ch;
	size_t				i;

	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == ch)
		{
			return ((void *)(ptr + i));
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	const char	*str = "Hello, world!";
// 	char		ch;
// 	char		*result;

// 	ch = 'o';
// 	result = ft_memchr(str, ch, strlen(str));
// 	if (result)
// 	{
// 		printf("'%c' が見つかりました。位置: %ld\n", ch, result - str);
// 	}
// 	else
// 	{
// 		printf("'%c' は見つかりませんでした。\n", ch);
// 	}
// 	return (0);
// }
