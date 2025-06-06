/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:15:00 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/02 17:03:43 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"
#include <stdlib.h>
#include <ctype.h>

void ft_write(const char *str)
{
    if (!str)
        return;
    write(1, str, ft_strlen(str));
}
int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

void free_split(char **arr) {
    int i = 0;
    if (!arr) return;
    while (arr[i]) {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int ft_isspace(int c)
{
    return (c == ' '  || c == '\t' || c == '\n' ||c == '\v' || c == '\f' || c == '\r');
}

double ft_atof(char *str)
{
    double res = 0.0;
    double frac = 0.0;
    double divisor = 1.0;
    int i = 0, sign = 1, after_dot = 0;
    int has_digit = 0;

    if (!str)
        ft_error("Error: Null string in ft_atof\n");

    while (ft_isspace(str[i]))
        i++;

    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+')
        i++;

    if (!ft_isdigit(str[i]) && str[i] != '.')
        ft_error("Error: Invalid number format (no digit)\n");

    while (str[i]) {
        if (str[i] == '.' && !after_dot) {
            after_dot = 1;
            i++;
            continue;
        }
        if(ft_isspace(str[i]))
            break;
        if (!ft_isdigit(str[i]))
            ft_error("Error: Invalid character in number\n");

        has_digit = 1;
        if (!after_dot)
            res = res * 10 + (str[i] - '0');
        else {
            frac = frac * 10 + (str[i] - '0');
            divisor *= 10.0;
        }
        i++;
    }
    if (!has_digit)
        ft_error("Error: No digit found in number\n");

    return sign * (res + frac / divisor);
}

void ft_error(const char *msg)
{
    write(2, msg, ft_strlen(msg));
    exit(EXIT_FAILURE);
}

int ft_count_words(const char *str, char delim)
{
    int count = 0;
    int i = 0;

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
    return count;
}

