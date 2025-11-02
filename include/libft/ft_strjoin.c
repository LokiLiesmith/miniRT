/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:22:29 by djanardh          #+#    #+#             */
/*   Updated: 2025/04/02 16:32:27 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// s1: The prefix string.
// s2: The suffix string.
// Return value: The new string. NULL if the allocation fails.
// Description:
// Allocates memory (using malloc(3)) and returns a new string,
// which is the result of concatening ’s1’ and ’s2’
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_string;
	size_t	newstr_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr_len = s1_len + s2_len + 1;
	new_string = malloc(newstr_len);
	if (new_string == NULL)
		return (NULL);
	ft_strlcpy(new_string, s1, newstr_len);
	ft_strlcat(new_string, s2, newstr_len);
	new_string[newstr_len - 1] = '\0';
	return (new_string);
}

// int	main(void)
// {
// 	const char *s1 = "";
// 	const char *s2 = "world";
// 	printf("%s\n", ft_strjoin(s1, s2));
// 	return (0);
// }