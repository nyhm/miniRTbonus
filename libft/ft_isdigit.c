/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:25:35 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/22 16:04:18 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	testChar;

// 	printf("文字を入力してください: ");
// 	scanf(" %c", &testChar);
// 	if (ft_isdigit(testChar))
// 	{
// 		printf("%c は数字です。\n", testChar);
// 	}
// 	else
// 	{
// 		printf("%c は数字ではありません。\n", testChar);
// 	}
// 	return (0);
// }
