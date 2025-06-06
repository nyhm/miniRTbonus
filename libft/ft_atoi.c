/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:25:07 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/25 15:09:49 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	is_flowl(int sign, long l, char next)
{
	if (sign == 1)
		if (LONG_MAX / 10 < l || (LONG_MAX / 10 == l && LONG_MAX % 10 <= next
				- '0'))
			return (1);
	if (sign == -1)
	{
		if (LONG_MIN / -10 < l)
			return (-1);
		else if ((LONG_MIN / -10 == l && LONG_MIN % -10 * -1 <= next - '0'))
			return (-1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	ret;
	int		sign;

	ret = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
		{
			if (is_flowl(sign, ret, *str) == 1)
				return ((int)LONG_MAX);
			if (is_flowl(sign, ret, *str) == -1)
				return ((int)LONG_MIN);
			ret = ret * 10 + (long)(*str - '0');
			str++;
		}
		else
			break ;
	}
	return ((int)(ret * sign));
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char str[] = "-9223372036854775807";
// 	printf("%d\n", atoi(str));
// 	printf("%d\n", ft_atoi(str));
// }