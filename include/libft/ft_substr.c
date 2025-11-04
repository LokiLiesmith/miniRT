/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:28:11 by djanardh          #+#    #+#             */
/*   Updated: 2025/04/08 18:43:39 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_malloc_size(size_t s_len, size_t start, size_t len)
{
	size_t	remaining_len;
	size_t	malloc_size;

	remaining_len = s_len - start;
	if (len < remaining_len)
		malloc_size = len;
	else
		malloc_size = remaining_len;
	return (malloc_size);
}

// s: The original string from which to create the substring.
// start: The starting index of the substring within ’s’.
// len: The maximum length of the substring.
// Allocates memory (using malloc(3)) and returns a substring from the string
// ’s’. The substring starts at index ’start’ and has a maximum length of ’len’
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub_string;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	sub_string = malloc(ft_malloc_size(s_len, start, len) + 1);
	if (sub_string == NULL)
		return (NULL);
	while (s[start] != '\0' && (i < len) && start < s_len)
	{
		sub_string[i] = s[start];
		i++;
		start++;
	}
	sub_string[i] = '\0';
	return (sub_string);
}

// int	main(void)
// {
// 	char *s = "helloworld";
// 	unsigned int start = 400;
// 	size_t len = 4;
// 	printf("%s\n", ft_substr(s, start, len));
// 	return (0);
// }