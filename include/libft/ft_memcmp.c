/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:42:25 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:32:05 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// DESCRIPTION:
// The memcmp() function compares byte string s1 against byte string s2.
// Both strings are assumed to be n bytes long.
// RETURN VALUES:
// The memcmp() function returns zero if the two strings are identical,
// otherwise returns the difference between the first two differing bytes
// (treated as unsigned char values, so that `\200' is greater than `\0',
// for example).  Zero-length strings are always identical.
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*r1;
	unsigned const char	*r2;
	size_t				i;

	i = 0;
	r1 = (unsigned char *)s1;
	r2 = (unsigned char *)s2;
	while (i < n)
	{
		if (r1[i] == r2[i])
			i++;
		else
			return (r1[i] - r2[i]);
	}
	if ((i == n) || (n == 0))
		return (0);
	else
		return (r1[i] - r2[i]);
}

// int	main(void)
// {
// 	const char *s1 = "abc";
// 	const char *s2 = "abc";
// 	size_t n = 7;
// 	printf("your fn: %d\n", ft_memcmp(s1, s2, n));
// 	printf("comp fn: %d\n", memcmp(s1, s2, n));
// 	return (0);
// }