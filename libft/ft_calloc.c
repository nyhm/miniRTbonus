/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:25:24 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/24 20:00:52 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size != 0 && count > (SIZE_MAX / size))
	{
		return (NULL);
	}
	ptr = malloc(count * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (ft_memset(ptr, 0, count * size));
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	int		*arr;
// 	size_t	num_elements;

// 	num_elements = 5;
// 	arr = (int *)ft_calloc(num_elements, sizeof(int));
// 	if (arr == NULL)
// 	{
// 		printf("Memory allocation failed\n");
// 		return (1);
// 	}
// 	for (size_t i = 0; i < num_elements; i++)
// 	{
// 		printf("arr[%zu] = %d\n", i, arr[i]);
// 	}
// 	free(arr);
// 	return (0);
// }
