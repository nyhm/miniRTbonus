/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:26:17 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/23 20:20:10 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (c + ('a' - 'A'));
	}
	return (c);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	test[] = "Hello, World!";

// 	// テスト
// 	for (int i = 0; test[i] != '\0'; i++)
// 	{
// 		printf("%c", ft_tolower(test[i]));
// 	}
// 	printf("\n");
// 	return (0);
// }
