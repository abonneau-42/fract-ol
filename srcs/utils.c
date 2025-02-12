/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:35:42 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/12 18:27:54 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_number(char *str)
{
	int	i;
	int in_decimal;
	
	i = 0;
	in_decimal = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '\0')
			return (0);
		i++;
	}
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (in_decimal)
				return (0);
			in_decimal = 1;
			i++;
			continue;
		}
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

double	ft_atof(const char *nptr)
{
	int		i;
	int		sign;
	double	result;
	double	decimal_part;
	double	divisor;

	i = 0;
	sign = 1;
	result = 0.0;
	decimal_part = 0.0;
	divisor = 10.0;

	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}

	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}

	if (nptr[i] == '.')
	{
		i++;
		while (nptr[i] >= '0' && nptr[i] <= '9')
		{
			decimal_part += (nptr[i] - '0') / divisor;
			divisor *= 10.0;
			i++;
		}
	}

	return (sign * (result + decimal_part));
}


int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
