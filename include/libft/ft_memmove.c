/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:29:35 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 21:16:48 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The memmove() function copies len bytes from string src to string
// dst.  The two strings may overlap; the copy is always done in a non-
// destructive manner.
// RETURN VALUES: The memmove() function returns the original value of dst.
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst2;
	const char	*src2;
	size_t		i;

	i = 0;
	dst2 = (char *)dst;
	src2 = (const char *)src;
	if (dst2 == NULL && src2 == NULL)
		return (NULL);
	if (dst2 > src2)
	{
		dst2 += len;
		src2 += len;
		while (len--)
			*(--dst2) = *(--src2);
	}
	else
	{
		while (len--)
		{
			*(dst2++) = *(src2++);
		}
	}
	return (dst);
}

// int	main(void)
// {
// 	char *d1 = "HelloWorld";
// 	const char *s1 = NULL;
// 	ft_memmove(d1, s1, 2);
// 	printf("your function: %s\n", d1);
// 	char *d2 = NULL;
// 	const char *s2 = NULL;
// 	memmove(d2, s2, 2);
// 	printf("computer function: %s\n", d2);
// 	return (0);
// }