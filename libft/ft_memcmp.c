/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:25:44 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/22 17:18:36 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1 = (const unsigned char *)s1;
	const unsigned char	*ptr2 = (const unsigned char *)s2;
	size_t				i;

	i = 0;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
		{
			return (ptr1[i] - ptr2[i]);
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	const char	str1[] = "abcadf";
// 	const char	str2[] = "abca";
// 	const char	str3[] = "abC";
// 	int			result1;
// 	int			result2;

// 	// 同じ文字列を比較
// 	result1 = ft_memcmp(str1, str2, strlen(str1));
// 	// 異なる文字列を比較
// 	result2 = ft_memcmp(str1, str3, strlen(str1));
// 	printf("Comparing str1 and str2: %d\n", result1); // 0 (等しい)
// 	printf("Comparing str1 and str3: %d\n", result2); // 正の値 (異なる)
// 	return (0);
// }
