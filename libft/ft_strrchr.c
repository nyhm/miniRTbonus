/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:26:14 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/24 15:57:30 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurrence;
	char	ch;

	last_occurrence = NULL;
	ch = (char)c;
	while (*s)
	{
		if (*s == ch)
		{
			last_occurrence = (char *)s;
		}
		s++;
	}
	if (ch == '\0')
	{
		return ((char *)s);
	}
	return (last_occurrence);
}

// #include <stdio.h>

// int main() {
//     const char *str = "Hello, World!";
//     char ch = 'o';

//     char *result = ft_strrchr(str, ch);
//     if (result) {
//         printf("Last occurrence of '%c': %s\n", ch, result);
//     } else {
//         printf("Character '%c' not found.\n", ch);
//     }

//     return (0);
// }
