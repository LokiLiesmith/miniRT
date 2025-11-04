/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:14:07 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:36:56 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Parameters: s: The string to output. fd: file descriptor on which to write.
// Description: Outputs the string ’s’ to the specified file descriptor.
void	ft_putstr_fd(char *s, int fd)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	write(fd, s, s_len);
}

// int	main(void)
// {
// 	char *print_string = "Cows are cute";
// 	ft_putstr_fd(print_string, 1);
// 	return (0);
// }