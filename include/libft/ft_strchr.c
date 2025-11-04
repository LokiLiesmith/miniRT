/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:27:27 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:40:16 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The strchr() function locates the first occurrence of c (converted to a
// char) in the string pointed to by s.  The terminating null character is
// considered to be part of the string; therefore if c is `\0', the func-
// tions locate the terminating `\0'.
// Return value: The functions strchr() return a pointer to the located
// character, or NULL if the character does not appear in the string.
char	*ft_strchr(const char *s, int c)
{
	char	a;
	size_t	i;
	size_t	s_len;

	a = (char)c;
	i = 0;
	s_len = ft_strlen(s);
	if (a == '\0')
		return ((char *)&s[s_len]);
	while (s[i] != '\0')
	{
		if (s[i] == a)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char *s = "gRdhsRdhf";
// 	int c = 'd';
// 	printf("%s\n", ft_strchr(s, c));
// 	printf("%s\n", strchr(s, c));
// 	return (0);
// }