/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:26:11 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/25 15:59:12 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_needle_length(const char *needle)
{
	size_t	needle_len;

	needle_len = 0;
	while (needle[needle_len] != '\0')
		needle_len++;
	return (needle_len);
}

// haystackからneedleを検索する関数
static char	*search_in_haystack(const char *haystack, const char *needle,
		size_t len, size_t needle_len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i <= len - needle_len)
	{
		j = 0;
		while (j < needle_len && haystack[i + j] == needle[j])
			j++;
		if (j == needle_len)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

// メインのft_strnstr関数
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	if (*needle == '\0')
		return ((char *)haystack);
	if (len == 0)
	{
		return (NULL);
	}
	if (*haystack == '\0')
		return (NULL);
	needle_len = get_needle_length(needle);
	if (needle_len > len)
		return (NULL);
	return (search_in_haystack(haystack, needle, len, needle_len));
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	const char	*haystack = "Hello, world!";
// 	const char	*needle1 = "world";
// 	const char	*needle2 = "notfound";
// 	const char	*needle3 = "";
// 	char		*result1;
// 	char		*result2;
// 	char		*result3;

// 	// テスト1: needle が見つかるケース
// 	result1 = ft_strnstr(haystack, needle1, 13);
// 	if (result1)
// 	{
// 		printf("Found '%s' in '%s': %s\n", needle1, haystack, result1);
// 	}
// 	else
// 	{
// 		printf("'%s' not found in '%s'\n", needle1, haystack);
// 	}
// 	// テスト2: needle が見つからないケース
// 	result2 = ft_strnstr(haystack, needle2, 13);
// 	if (result2)
// 	{
// 		printf("Found '%s' in '%s': %s\n", needle2, haystack, result2);
// 	}
// 	else
// 	{
// 		printf("'%s' not found in '%s'\n", needle2, haystack);
// 	}
// 	// テスト3: 空の needle
// 	result3 = ft_strnstr(haystack, needle3, 13);
// 	if (result3)
// 	{
// 		printf("Found empty needle in '%s': %s\n", haystack, result3);
// 	}
// 	else
// 	{
// 		printf("Empty needle not found in '%s'\n", haystack);
// 	}
// 	// テスト4: len を超える検索
// 	char *result4 = ft_strnstr(haystack, needle1, 5); // "Hello" までしか検索しない
// 	if (result4)
// 	{
// 		printf("Found '%s' in '%s': %s\n", needle1, haystack, result4);
// 	}
// 	else
// 	{
// 		printf("'%s' not found in '%s' within length 5\n", needle1, haystack);
// 	}
// 	return (0);
// }
