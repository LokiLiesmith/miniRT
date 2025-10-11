/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:53:18 by djanardh          #+#    #+#             */
/*   Updated: 2025/10/11 21:53:29 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_input(int ac, char **av)
{
	int		file_len;
	char	*temp;

	if (ac != 2)
		return (printf("Usage: './miniRT scene_file.rt'\n"), 1);
	file_len = ft_strlen(av[1]);
	// minimum one char for file name?
	if (file_len < 4)
		return (printf("Invalid filename\n"), 1);
	// check if extension is correct (assuming it is case-sensitive?)
	temp = ft_substr(av[1], file_len - 3, 3);
	if (ft_strncmp(temp, ".rt", 3) != 0)
		return (printf("Invalid file extension\n"), 1);
	free(temp);
	return (0);
}
