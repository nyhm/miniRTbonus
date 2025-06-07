/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:15:00 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 10:58:27 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

size_t	count_array(char **arr);
void	ft_write(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	free_split(char **arr);
int		ft_isspace(int c);

size_t	count_array(char **arr)
{
	size_t	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

void	ft_write(const char *str)
{
	if (!str)
		return ;
	write(1, str, ft_strlen(str));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}
