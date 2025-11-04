/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:47:43 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 16:55:14 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Parameters
// s1: The string to be trimmed.
// set: The string containing the set of characters to be removed.
// Return value: The trimmed string
// Description:
// Allocates memory (using malloc(3)) and returns a copy of ’s1’ with characters
// from ’set’ removed from the beginning and the end.
static int	in_set_or_not(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
		{
			return (1);
		}
		else
		{
			i++;
		}
	}
	return (0);
}

static size_t	ft_start_index(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (in_set_or_not(s1[i], set) == 1)
			i++;
		else
		{
			return (i);
		}
	}
	return (i);
}

static size_t	ft_end_index(char const *s1, char const *set, size_t s1_len,
		size_t start_index)
{
	size_t	i;

	i = s1_len - 1;
	if (start_index >= s1_len)
		return (start_index);
	while (i > start_index)
	{
		if (in_set_or_not(s1[i], set) == 1)
			i--;
		else
		{
			return (i);
		}
	}
	return (start_index);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start_index;
	size_t	end_index;
	char	*trimmed_string;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	if (s1 == NULL || set == NULL)
		return (NULL);
	if (s1_len == 0)
		return (ft_strdup(""));
	start_index = ft_start_index(s1, set);
	end_index = ft_end_index(s1, set, s1_len, start_index);
	trimmed_string = ft_substr(s1, start_index, (end_index - start_index + 1));
	return (trimmed_string);
}

// int	main(void)
// {
// 	char const *s1 = "ababaaaMy name is Simonbbaaabba";
// 	char const *set = "ab";
// 	printf("%s\n", ft_strtrim(s1, set));
// 	return (0);
// }