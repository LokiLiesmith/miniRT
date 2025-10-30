/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:51:40 by djanardh          #+#    #+#             */
/*   Updated: 2025/10/30 20:04:47 by djanardh         ###   ########.fr       */
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

int parse_xyz(char *s, double xyz[3])
{
	char **sub_strs;
	sub_strs = ft_split(s, ',');
	if (!sub_strs)
		return (printf("Error\nft_split malloc fail in parse_xyz\n"), 1);
	int i;
	i = 0;
	while (sub_strs[i] && i < 3)
	{
		if (!is_valid_double(sub_strs[i], 0))
			return (free_split(sub_strs), printf("Error\nInvalid char for params\n"), 1);
		xyz[i] = ft_atod(sub_strs[i]);
		i++;
	}
	if (i != 3)
		return (free_split(sub_strs), printf("Error\nLess than 3 values for coords/vec\n"), 1);
	if (sub_strs[3] != NULL)
		return (free_split(sub_strs), printf("Error\nMore than 3 values for coords/vec\n"), 1);
	free_split(sub_strs);
	return (0);
}

int	parse_rgb(char *rgb_str, t_color *color)
{
	char	**rgb;
	long	values[3];
	int		i;

	rgb = ft_split(rgb_str, ',');
	if (!rgb)
		return (printf("Error\nMemory allocation failed\n"), 1);
	i = 0;
	while (i < 3)
	{
		if (rgb[i] == NULL)
			return (free_split(rgb), printf("Error\nRGB must have 3 values\n"),
				1);
		if (check_if_int(rgb[i]) != 0)
			return (free_split(rgb), printf("Error\nInvalid RGB format\n"), 1);
		values[i] = ft_atol(rgb[i]);
		if (values[i] < 0 || values[i] > 255)
			return (free_split(rgb),
				printf("Error\nRGB out of range [0-255]\n"), 1);
		i++;
	}
	if (rgb[3] != NULL)
		return (free_split(rgb), printf("Error\nToo many RGB values\n"), 1);
	color->r = values[0];
	color->g = values[1];
	color->b = values[2];
	free_split(rgb);
	return (0);
}
