/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:42:44 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/24 20:03:16 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*dst;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		substr = (char *)malloc(1);
		if (substr)
			substr[0] = '\0';
		return (substr);
	}
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	dst = substr;
	s += start;
	while (len--)
		*dst++ = *s++;
	*dst = '\0';
	return (substr);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	*s;
// 	char	*result;

// 	s = "Hello, World!";
// 	// 例1: "Hello, World!" の 7文字目から5文字を抽出
// 	result = ft_substr(s, 7, 5);
// 	if (result)
// 	{
// 		printf("Result: %s\n", result); // 出力: "World"
// 		free(result);                   // メモリ解放
// 	}
// 	// 例2: 開始位置が文字列の長さを超えている場合
// 	result = ft_substr(s, 20, 5);
// 	if (result)
// 	{
// 		printf("Result: '%s'\n", result); // 出力: 空文字列 ''
// 		free(result);                     // メモリ解放
// 	}
// 	// 例3: 開始位置が0で、文字列全体をコピーする場合
// 	result = ft_substr(s, 0, 5);
// 	if (result)
// 	{
// 		printf("Result: %s\n", result); // 出力: "Hello"
// 		free(result);                   // メモリ解放
// 	}
// 	return (0);
// }
