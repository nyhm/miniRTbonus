/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:52:43 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 16:00:31 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

void	ft_atof2(char *str, int i, double *res, double *divisor)
{
	int	after_dot;
	int	has_digit;

	after_dot = 0;
	has_digit = 0;
	while (str[i])
	{
		if (str[i] == '.' && !after_dot)
		{
			after_dot = 1;
			i++;
			continue ;
		}
		if (ft_isspace(str[i]))
			break ;
		if (!ft_isdigit(str[i]))
			ft_error("Error: Invalid character in number\n");
		has_digit = 1;
		*res = *res * 10 + (str[i] - '0');
		if (after_dot)
			*divisor *= 10.0;
		i++;
	}
	if (!has_digit)
		ft_error("Error: No digit found in number\n");
}

double	ft_atof(char *str)
{
	int		i;
	double	res;
	double	divisor;
	int		sign;

	res = 0.0;
	divisor = 1.0;
	i = 0;
	sign = 1;
	if (!str)
		ft_error("Error: Null string in ft_atof\n");
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]) && str[i] != '.')
		ft_error("Error: Invalid number format (no digit)\n");
	ft_atof2(str, i, &res, &divisor);
	return (sign * (res / divisor));
}

void	ft_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

int	ft_count_words(const char *str, char delim)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == delim)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && str[i] != delim)
				i++;
		}
	}
	return (count);
}
