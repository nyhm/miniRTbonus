/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:25:49 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/25 15:28:26 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	if (dest == NULL && src == NULL && n > 0)
		return (NULL);
	s = (const char *)src;
	d = (char *)dest;
	if (s < d && d < s + n)
	{
		i = n;
		while (i-- > 0)
			d[i] = s[i];
	}
	else
	{
		i = 0;
		while (i++ < n)
			d[i - 1] = s[i - 1];
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	str[] = "Hello, World!";

// 	// メモリが重なる場合のテスト（`str + 7` に `str` を移動）
// 	printf("Before memmove: %s\n", str);
// 	ft_memmove(str + 7, str, 6);
// 	printf("After memmove: %s\n", str);
// 	return (0);
// }
