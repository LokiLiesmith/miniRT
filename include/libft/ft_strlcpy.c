/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:48:34 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:44:18 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// strlcpy() take the full size of the destination buffer
// and guarantee NUL-termination if there is room.  Note that room for
// the NUL should be included in dstsize.
// strlcpy() copies up to dstsize - 1 characters from the string src to
// dst, NUL-terminating the result if dstsize is not 0.
// the strlcpy() return the total length of the string they tried to create.
// For strlcpy() that means the length of src.
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (src[count] != '\0')
		count++;
	if (dstsize > 0)
	{
		while ((src[i] != '\0') && (i < (dstsize - 1)))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (count);
}

// int	main(void)
// {
// 	char	destination[] = "kill";
// 	char	*source;
// 	size_t	size;

// 	source = "Helloworld";
// 	size = 0;
// 	printf("your fn output: %zu\n", ft_strlcpy(destination, source, size));
// 	printf("comp fn output: %lu\n", strlcpy(destination, source, size));
// 	return (0);
// }
