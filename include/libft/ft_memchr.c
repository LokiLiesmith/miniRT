/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:41:27 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:30:52 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// DESCRIPTION:
// The memchr() function locates the first occurrence of c (converted to an
// unsigned char) in string s.
// RETURN VALUES:
// The memchr() function returns a pointer to the byte located, or NULL if
// no such byte exists within n bytes.
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	d;
	unsigned char	*s2;
	size_t			i;

	d = (unsigned char)c;
	s2 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s2[i] == d)
		{
			return ((char *)&s2[i]);
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char *s = NULL;
// 	printf("%s\n", memchr(s, 'l', 4));
// 	printf("%s\n", ft_memchr(s, 'l', 4));
// 	return (0);
// }