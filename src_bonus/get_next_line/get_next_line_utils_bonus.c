/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 06:29:08 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/06 22:36:42 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

char	*ft_error_read(char *buff);
char	*ft_error_join(char *left_str, char *buff);

char	*ft_error_read(char *buff)
{
	write(2, "Error reading file\n", 19);
	free(buff);
	return (NULL);
}

char	*ft_error_join(char *left_str, char *buff)
{
	write(2, "Error joining strings\n", 22);
	free(buff);
	free(left_str);
	return (NULL);
}
