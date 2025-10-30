/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:51:40 by djanardh          #+#    #+#             */
/*   Updated: 2025/10/30 18:51:43 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	is_valid_double(char *str, int has_dot)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (str[i] >= '0' && str[i] <= '9')
			has_digit = 1;
		else
			return (0);
		i++;
	}
	return (has_digit);
}

void	free_split(char **split_strs)
{
	int	i;

	if (!split_strs)
		return ;
	i = 0;
	while (split_strs[i])
	{
		free(split_strs[i]);
		i++;
	}
	free(split_strs);
}

int	count_split(char **split_strs)
{
	int	count;

	if (!split_strs)
		return (-1);
	count = 0;
	while (array[count] != NULL)
		count++;
	return (count);
}
