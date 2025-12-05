/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:29:35 by djanardh          #+#    #+#             */
/*   Updated: 2025/12/05 16:16:28 by mrazem           ###   ########.fr       */
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
