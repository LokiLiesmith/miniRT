/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:50:04 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:23:21 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The isprint() function tests for any printing character, including space
// (` ').
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (1);
	}
	return (0);
}

// int main(void)
// {
// 	int output_yours = ft_isprint('\'');
// 	printf("your output: %i\n", output_yours);
// 	int output_comp = isprint('\'');
// 	printf("in-built function output: %i\n", output_comp);
// 	return(0);
// }
