/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 23:23:59 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/24 19:31:34 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

// メインのft_itoa関数
char	*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	unsigned int	num;

	len = count_digits(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		num = -n;
	}
	else
		num = n;
	while (len > 0 && (n >= 0 || len > 1))
	{
		if (n < 0 && len == 1)
			break ;
		str[--len] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}

// // 整数の桁数を計算する関数
// static size_t	count_digits(int n)
// {
// 	size_t	count;

// 	if (n <= 0)
// 		count = 1;
// 	else
// 		count = 0;
// 	while (n != 0)
// 	{
// 		n /= 10;
// 		count++;
// 	}
// 	return (count);
// }

// // メインのft_itoa関数
// char	*ft_itoa(int n)
// {
// 	char			*str;
// 	size_t			len;
// 	unsigned int	num;

// 	len = count_digits(n);
// 	str = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!str)
// 		return (NULL);
// 	str[len] = '\0';
// 	if (n < 0)
// 	{
// 		str[0] = '-';
// 		num = -n;
// 	}
// 	else
// 		num = n;
// 	while (len-- > 0 && str[len] != '-')
// 	{
// 		str[len] = num % 10 + '0';
// 		num /= 10;
// 	}
// 	return (str);
// }
