/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:26:20 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/23 20:24:36 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c + ('A' - 'a'));
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
// 		printf("%c", ft_toupper(test[i]));
// 	}
// 	printf("\n");
// 	return (0);
// }
