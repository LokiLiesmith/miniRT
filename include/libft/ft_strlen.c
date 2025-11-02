/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:57:46 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:45:24 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// DESCRIPTION:
//     The strlen() function computes the length of the string s. The strnlen()
//     function attempts to compute the length of s, but never scans beyond the
//     first maxlen bytes of s.
// RETURN VALUES:
//     The strlen() function returns the number of characters that precede the
//     terminating NUL character.
size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

// int	main(void)
// {
// 	size_t output_yours = ft_strlen("[]\\ ");
// 	printf("your output: %zu\n", output_yours);
// 	size_t output_comp = strlen("[]\\ ");
// 	printf("in-built function output: %zu\n", output_comp);
// 	return (0);
// }