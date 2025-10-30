/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:51:53 by djanardh          #+#    #+#             */
/*   Updated: 2025/10/30 20:01:44 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	skip_whitespace_and_sign(char *str, int *sign)
{
	int	i;

	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

static int	parse_integer_part(char *str, int *i)
{
	int	integer;

	integer = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		integer = integer * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (integer);
}

static double	parse_decimal_part(char *str, int *i)
{
	double	decimal;
	int		count;

	decimal = 0;
	count = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		decimal = decimal * 10 + (str[*i] - '0');
		count++;
		(*i)++;
	}
	return (decimal / pow(10, count));
}

double	ft_atod(char *str)
{
	int		i;
	int		sign;
	int		integer;
	double	decimal;

	sign = 1;
	i = skip_whitespace_and_sign(str, &sign);
	if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '.'))
		return (0);
	integer = parse_integer_part(str, &i);
	decimal = 0;
	if (str[i] == '.')
	{
		i++;
		decimal = parse_decimal_part(str, &i);
	}
	return ((integer + decimal) * sign);
}

long	ft_atol(char *str)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
