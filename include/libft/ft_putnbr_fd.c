/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:06:00 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/18 19:25:02 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Outputs the integer ’n’ to the specified file descriptor.
void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n < 10 && n >= 0)
	{
		c = '0' + n;
		write(fd, &c, 1);
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		c = '0' + (n % 10);
		write(fd, &c, 1);
	}
}

// int	main(void)
// {
// 	int n = 12345;
// 	ft_putnbr_fd(n, 1);
// 	return (0);
// }