/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:31:19 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:47:20 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The strnstr() function locates the first occurrence of the null-termi-nated
// string needle in the string haystack, where not more than len characters are
// searched.  Characters that appear after a `\0' character are not searched.
// RETURN VALUES: If needle is an empty string, haystack is returned; if needle
// occurs nowhere in haystack, NULL is returned; otherwise a pointer to the
// first character of the first occurrence of needle is returned.
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while ((needle[j] == haystack[i + j]) && (needle[j] != '\0') && ((i
					+ j) < len))
		{
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*haystack;
// 	char	*needle;
// 	size_t	len;

// 	haystack = "helloworld";
// 	needle = "llow";
// 	len = 7;
// 	printf("%s\n", ft_strnstr(haystack, needle, len));
// 	printf("%s\n", strnstr(haystack, needle, len));
// 	return (0);
// }
