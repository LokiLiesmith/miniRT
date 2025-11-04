/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:43:05 by djanardh          #+#    #+#             */
/*   Updated: 2025/11/04 21:34:47 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// In ASCII, whitespace characters are space ( ' ' ), tab ( '\t' ),
// carriage return ( '\r' ), newline ( '\n' ),
// vertical tab ( '\v' ) and formfeed ( '\f' ).
#include "libft.h"

// The atoi() function converts the initial portion of the string pointed to by
// str to from ASCII to int representation.
int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

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

// int	main(void)
// {
// 	const char *str = "0hf";
// 	printf("your atoi: %d\n", ft_atoi(str));
// 	printf("actual atoi: %d\n", atoi(str));
// 	return (0);
// }