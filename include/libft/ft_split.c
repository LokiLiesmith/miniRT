/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:03:31 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:38:15 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Parameters: s: The string to be split.
//             c: The delimiter character.

// The array of new strings resulting from the split.NULL if the allocation
//  fails.

// 	Allocates memory(using malloc(3)) and
// 	returns an array of strings obtained by splitting ’s’ using the character
//     ’c’ as a delimiter.The array must end with a NULL pointer.

#include "libft.h"

static unsigned int	ft_word_count(const char *s, char c)
{
	unsigned int	count;
	int				flag;

	if (!s)
		return (0);
	count = 0;
	flag = 0;
	while (*s)
	{
		if (*s != c && !flag)
		{
			flag = 1;
			count++;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (count);
}

static void	ft_free_memory(char **split_strings, size_t count_array)
{
	while (count_array--)
		free(split_strings[count_array]);
	free(split_strings);
}

static char	*ft_allocate_word(char const *s, unsigned int start,
		unsigned int end)
{
	char	*word;

	word = ft_substr(s, start, end - start + 1);
	if (!word)
		return (NULL);
	return (word);
}

static char	**ft_fill_array(char const *s, char c, char **split_strings,
		int count)
{
	unsigned int	start;
	unsigned int	end;
	int				i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != '\0')
			{
				if (s[i + 1] == c || s[i + 1] == '\0')
				{
					end = i;
					split_strings[++count] = ft_allocate_word(s, start, end);
					if (!split_strings[count])
						return (ft_free_memory(split_strings, count), NULL);
					break ;
				}
				i++;
			}
		}
	}
	return (split_strings[count + 1] = NULL, split_strings);
}

// Parameters: s: The string to be split. c: The delimiter character.
// Return value: The array of new strings resulting from the split.
// NULL if the allocation fails.
// Description: Allocates memory (using malloc(3)) and returns an array of
// strings obtained by splitting ’s’ using the character ’c’ as a delimiter.
// The array must end with a NULL pointer.
char	**ft_split(char const *s, char c)
{
	char			**split_strings;
	int				count;
	unsigned int	word_count;

	word_count = ft_word_count(s, c);
	count = -1;
	if (!s)
		return (NULL);
	split_strings = malloc((ft_word_count(s, c) + 1) * sizeof(char *));
	if (!split_strings)
		return (NULL);
	return (ft_fill_array(s, c, split_strings, count));
}

// int	main(void)
// {
// 	const char *s = "                  olol";
// 	char c = ' ';
// 	printf("%u\n", ft_word_count(s, c));
// 	char **result = ft_split(s, c);
// 	unsigned int i = 0;
// 	while (result[i])
// 	{
// 		printf("split_string[%u] = %s\n", i, result[i]);
// 		i++;
// 	}
// 	ft_free_memory(result, i);
// 	return (0);
// }