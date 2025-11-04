/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:50:21 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:56:03 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The strduplication() function allocates sufficient memory for a copy of the
// string s1, does the copy, and returns a pointer to it.  The pointer may
// subsequently be used as an argument to the function free(3).
// If insufficient memory is available, NULL is returned and errno is set to
// ENOMEM.
char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	str_len;
	int		i;

	i = 0;
	str_len = ft_strlen(s1);
	s2 = malloc(str_len + 1);
	if (s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return ((char *)s2);
}

// int	main(void)
// {
// 	const char *s1 = "hello";
// 	printf("%s\n", ft_strdup(s1));
// 	printf("%s\n", strdup(s1));
// 	return (0);
// }