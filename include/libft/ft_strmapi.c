/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:07:17 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:46:07 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Parameters: s : string to iterate over. f : fn to apply to each character
// Return value:
// The string created from the successive applications of ’f’.Returns NULL if
// the allocation fails.
// Description:
// Applies the function f to each character of the string s, passing its index
// as the first argument and the character itself as the second.A new string is
// created(using malloc(3)) to store the results from the successive
// applications of f.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;
	size_t			s_len;

	if (s == NULL || f == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	result = malloc(s_len + 1);
	if (result == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		result[i] = f(i, (char)s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// char	to_upper(unsigned int i, char c)
// {
// 	(void)i;
// 	return (ft_toupper(c));
// }

// int	main(void)
// {
// 	char	*s;

// 	s = "SDKHFDFfjhjkDKFG";
// 	printf("%s\n", ft_strmapi(s, to_upper));
// 	return (0);
// }
