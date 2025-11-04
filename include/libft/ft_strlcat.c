/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:08:26 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:42:59 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// strlcat() take the full size of the destination buffer and guarantee
// NUL-termination if there is room. The NULL should be included in dstsize.
// strlcat() appends string src to the end of dst.  It will append at most
// dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate,
// unless dstsize is 0 or the original dst string was longer than dstsize
// (in practice this should not happen as it means that either dstsize is
// incorrect or that dst is not a proper string).
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while ((src[i] != '\0' && (dst_len + i < dstsize - 1)))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// int	main(void)
// {
// 	char *dst = "hello";
// 	char *src = "worldhjgh";
// 	size_t dstsize = 2;
// 	printf("your fn: %zu\n", ft_strlcat(dst, src, dstsize));
// 	printf("comp fn: %zu\n", strlcat(dst, src, dstsize));
// 	return (0);
// }