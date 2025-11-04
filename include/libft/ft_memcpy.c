/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:00:41 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 21:16:13 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The memcpy() function copies n bytes from memory area src to memory
// area dst.  If dst and src overlap, behavior is undefined.  Applica-
// tions in which dst and src might overlap should use memmove(3)
// instead.
// RETURN VALUES: The memcpy() function returns the original value of dst.
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dst2;
	const char	*src2;

	src2 = (const char *)src;
	dst2 = (char *)dst;
	i = 0;
	if (dst2 == NULL && src2 == NULL)
	{
		return (NULL);
	}
	while (i < n)
	{
		dst2[i] = src2[i];
		i++;
	}
	return (dst);
}

// int	main(void)
// {
// 	char s1[10] = "Hello";
// 	char d1[10];
// 	ft_memcpy(d1, s1, 3);
// 	printf("your output: %s\n", d1);
// 	printf("%d\n", d1[5]);
// 	char d4[10] = "abcdef";
// 	memcpy(d4, s1, 5);
// 	printf("your output: %s\n", d4);
// 	printf("%d\n", d4[5]);
// 	char d2[10];
// 	memcpy(d2, s1, 3);
// 	printf("in-built function output: %s\n", d2);
// 	printf("%d\n", d2[5]);
// 	char d3[10] = "abcdef";
// 	memcpy(d3, s1, 5);
// 	printf("in-built function output: %s\n", d3);
// 	printf("%d\n", d3[5]);
// 	return (0);
// }