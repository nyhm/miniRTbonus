/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:25:55 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/23 18:00:41 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	if (c == '\0')
	{
		return ((char *)str);
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char	*str = "Hello, World!";
// 	char		*result;

// 	// 文字 'W' を検索
// 	result = ft_strchr(str, 'W');
// 	if (result != NULL)
// 	{
// 		printf("Character found: %s\n", result);
// 	}
// 	else
// 	{
// 		printf("Character not found.\n");
// 	}
// 	return (0);
// }
