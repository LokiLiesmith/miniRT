/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:36:28 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:35:28 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Note:  ssize_t write(int fildes, const void *buf, size_t nbyte);

#include "libft.h"

// Parameters: c: The character to output. fd:file descriptor on which to write
// Description: Outputs the character ’c’ to the specified file descriptor.
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// int	main(void)
// {
// 	char c = 'a';
// 	ft_putchar_fd(c, fd);
// 	return (0);
// }
// Handling Errors:
// Since write() can fail, you should always consider:
// Invalid file descriptors (fd is negative or closed)
// Permission issues (e.g., trying to write to a read-only file)
// Full disk or I/O errors