/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 22:50:04 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 11:57:03 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	char	*original_dest;

	original_dest = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (original_dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len2;
	size_t	len1;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcpy(result + len1, s2);
	return (result);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	*s1;
// 	char	*s2;
// 	char	*result;

// 	s1 = "Hello, ";
// 	s2 = "World!";
// 	// 2つの文字列を連結
// 	result = ft_strjoin(s1, s2);
// 	if (result)
// 	{
// 		printf("Result: %s\n", result); // 出力: "Hello, World!"
// 		free(result);                   // メモリ解放
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed\n");
// 	}
// 	// もう一つのテスト
// 	s1 = "Foo";
// 	s2 = "Bar";
// 	result = ft_strjoin(s1, s2);
// 	if (result)
// 	{
// 		printf("Result: %s\n", result); // 出力: "FooBar"
// 		free(result);                   // メモリ解放
// 	}
// 	return (0);
// }
