/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:26:06 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/22 08:12:52 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
	{
		len++;
	}
	return (len);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	A[] = "asdfgh";

// 	printf("%zu\n", ft_strlen(A));
// 	return (0);
// }
