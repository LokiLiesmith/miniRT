/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:29:08 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:48:52 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The toupper() function converts a lower-case letter to the corresponding
// upper-case letter.
int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c = c - 32;
	}
	return (c);
}

// int	main(void)
// {
// 	int output = ft_toupper('a');
// 	printf("your fn: %c", output);
// 	return (0);
// }