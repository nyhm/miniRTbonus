/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:25:27 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/22 15:56:06 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9'));
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	testChar;

// 	printf("文字を入力してください: ");
// 	scanf(" %c", &testChar);
// 	if (ft_isalnum(testChar))
// 	{
// 		printf("%c はアルファベットまたは数字です。\n", testChar);
// 	}
// 	else
// 	{
// 		printf("%c はアルファベットでも数字でもありません。\n", testChar);
// 	}
// 	return (0);
// }
