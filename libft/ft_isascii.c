/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:25:32 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/22 16:01:04 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return ((c >= 0 && c <= 127));
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	testChar;

// 	printf("文字の整数値を入力してください: ");
// 	scanf("%d", &testChar);
// 	if (ft_isascii(testChar))
// 	{
// 		printf("%d はASCII文字です。\n", testChar);
// 	}
// 	else
// 	{
// 		printf("%d はASCII文字ではありません。\n", testChar);
// 	}
// 	return (0);
// }
