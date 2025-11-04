/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:39:02 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:48:43 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The tolower() function converts an upper-case letter to the corresponding
// lower-case letter.
// RETURN VALUES
// If the argument is an upper-case letter, the tolower() function returns
// the corresponding lower-case letter if there is one; otherwise,
// the argument is returned unchanged.
int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c = c + 32;
	}
	return (c);
}

// int	main(void)
// {
// 	int output = ft_tolower('A');
// 	printf("your fn: %c", output);
// 	return (0);
// }