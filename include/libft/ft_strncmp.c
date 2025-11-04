/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:49:38 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:47:03 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//      The strncmp() function compares not more than n characters.  Because
//      strncmp() is designed for comparing strings rather than binary data,
//      characters that appear after a `\0' character are not compared.
// RETURN VALUES:
//      The strncmp() functions return an integer greater than,
//      equal to, or less than 0, according as the string s1 is greater than,
//      equal to, or less than the string s2.  The comparison is done using
//      unsigned characters, so that `\200' is greater than `\0'.
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			num;
	size_t			i;
	unsigned char	*r1;
	unsigned char	*r2;

	i = 0;
	num = 0;
	r1 = (unsigned char *)s1;
	r2 = (unsigned char *)s2;
	while ((n != 0) && (i < n) && ((r1[i] != '\0') || (r2[i] != '\0')))
	{
		if (r1[i] != r2[i])
		{
			num = r1[i] - r2[i];
			return (num);
		}
		i++;
	}
	return (num);
}

// int	main(void)
// {
// 	const char *string3 = "abc";
// 	const char *string4 = "abcd";
// 	size_t n = 4;
// 	printf("%d\n", ft_strncmp(string3, string4, n));
// 	printf("%d\n", strncmp(string3, string4, n));
// 	return (0);
// }