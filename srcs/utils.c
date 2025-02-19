/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:35:42 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/19 10:59:37 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_number(char *str)
{
	int	i;
	int	in_decimal;

	i = 0;
	in_decimal = 0;
	if ((str[i] == '-' || str[i] == '+') && str[i + 1] != '\0')
		i++;
	else if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (in_decimal)
				return (0);
			in_decimal = 1;
			i++;
			continue ;
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
	unsigned int	i;
	int				sign;
	t_dvector		result;
	double			divisor;

	i = 0;
	sign = 1;
	result = (t_dvector){.x = 0.0, .y = 0.0};
	divisor = 10.0;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result.x = result.x * 10 + (nptr[i++] - '0');
	if (nptr[i++] == '.')
	{
		while (nptr[i] >= '0' && nptr[i] <= '9')
		{
			result.y += (nptr[i++] - '0') / divisor;
			divisor *= 10.0;
		}
	}
	return (sign * (result.x + result.y));
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

int	is_float(char *chr, t_vars *ctx, int index)
{
	double	value;

	if (!is_number(chr))
		return (0);
	if (ft_strlen(chr) > 11)
		return (0);
	value = ft_atof(chr);
	if (value < -2147483648 || value > 2147483647)
		return (0);
	ctx->params[index] = value;
	return (1);
}
