/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:30:35 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:25:12 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_int_len(long n)
{
	long	i;

	i = 0;
	if (n < 0)
	{
		n = n * (-1);
		while (n >= 10)
		{
			n = n / 10;
			i++;
		}
		return (i + 2);
	}
	if (n == 0)
		return (1);
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

static char	*ft_posnum(long i, long temp, char *str)
{
	while (i >= 0)
	{
		str[i] = (temp % 10) + '0';
		temp = temp / 10;
		i--;
	}
	return (str);
}

static char	*ft_negnum(long i, long temp, char *str)
{
	while (i > 0)
	{
		str[i] = (temp % 10) + '0';
		temp = temp / 10;
		i--;
	}
	return (str);
}

// Parameters: n: The integer to convert.
// Return value: The string representing the integer. NULL if the allocation
// fails.
// Description: Allocates memory (using malloc(3)) and returns
// a string representing the integer received as an argument. Negative numbers
// must be handled.
char	*ft_itoa(int n)
{
	long	i;
	char	*str;
	long	temp;

	temp = n;
	i = ft_int_len(temp);
	str = malloc(ft_int_len(temp) + 1);
	if (str == NULL)
		return (NULL);
	if (temp < 0)
	{
		temp = -temp;
		str[0] = '-';
		str[i] = '\0';
		return (ft_negnum(i - 1, temp, str));
	}
	str[i] = '\0';
	return (ft_posnum(i - 1, temp, str));
}

// int	main(void)
// {
// 	printf("%lu\n", ft_int_len(-4564560));
// 	printf("%s\n", ft_itoa(-4564560));
// 	return (0);
// }
