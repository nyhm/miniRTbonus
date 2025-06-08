/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:56:32 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 16:14:03 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

t_color	color_mul(t_color a, t_color b);
t_color	color_scale(t_color color, double scale);
int		is_strict_integer(const char *str);
int		is_empty_or_comment(char *line);
int		has_rt_extension(const char *filename);

t_color	color_mul(t_color a, t_color b)
{
	return ((t_color){a.r * b.r, a.g * b.g, a.b * b.b});
}

t_color	color_scale(t_color color, double scale)
{
	return ((t_color){color.r * scale, color.g * scale, color.b * scale});
}

int	is_strict_integer(const char *str)
{
	int	len;
	int	end;
	int	i;

	len = ft_strlen(str);
	end = len - 1;
	while (end >= 0 && (str[end] == '\n' || str[end] == ' ' \
			|| str[end] == '\t'))
		end--;
	if (end < 0)
		return (0);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (i > end)
		return (0);
	while (i <= end)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	is_empty_or_comment(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\t' || line[i] == '#' || line[i] == '\n')
		return (1);
	return (0);
}

int	has_rt_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len <= 3)
		return (0);
	return (ft_strcmp(filename + len - 3, ".rt") == 0 && \
		filename[len - 4] != '/');
}
