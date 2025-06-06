/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:26:08 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/24 00:24:01 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
	{
		return (0);
	}
	while (n--)
	{
		if (*s1 != *s2)
		{
			return ((unsigned char)*s1 - (unsigned char)*s2);
		}
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return (0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

// int	main(int argc, char *argv[])
// {
// 	if (argc != 4)
// 	{
// 		printf("Usage: %s <string1> <string2> <n>\n", argv[0]);
// 		return (1);
// 	}

// 	int n = atoi(argv[3]);
// 	if (n < 0)
// 	{
// 		printf("数値を変えてください。\n");
// 		return (1);
// 	}

// 	int result;
// 	result = strncmp(argv[1], argv[2], n);
// 	printf("理想 %d\n", result);
// 	printf("現実 %d\n", ft_strncmp(argv[1], argv[2], n));
// 	return (0);
// }