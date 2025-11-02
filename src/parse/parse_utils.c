/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:51:40 by djanardh          #+#    #+#             */
/*   Updated: 2025/11/02 23:08:31 by djanardh         ###   ########.fr       */
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
	while (split_strs[count] != NULL)
		count++;
	return (count);
}

int	is_line_empty_or_whitespace(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

void	strip_newline(char *line)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\r')
		{
			line[i] = '\0';
			break ;
		}
		i++;
	}
}
