/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xyz_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 20:41:11 by djanardh          #+#    #+#             */
/*   Updated: 2025/11/02 23:08:34 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_if_int(char *str)
{
	int	count;

	if (!str || !str[0])
		return (1);
	count = 0;
	if (str[0] == '-' || str[0] == '+')
		count++;
	if (!str[count])
		return (1);
	while (str[count] != '\0')
	{
		if (str[count] < '0' || str[count] > '9')
			return (1);
		count++;
	}
	return (0);
}

int	parse_rgb(char *rgb_str, t_color *color, int i)
{
	char	**rgb;
	long	values[3];

	rgb = ft_split(rgb_str, ',');
	if (!rgb)
		return (printf("Error\nMemory allocation failed\n"), 1);
	while (i < 3)
	{
		if (rgb[i] == NULL)
			return (free_split(rgb), printf("Error\nRGB must've 3 nos.\n"), 1);
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

int	parse_xyz(char *s, double xyz[3])
{
	char	**sub_strs;
	int		i;

	sub_strs = ft_split(s, ',');
	if (!sub_strs)
		return (printf("Error\nft_split malloc fail in parse_xyz\n"), 1);
	i = 0;
	while (sub_strs[i] && i < 3)
	{
		if (!is_valid_double(sub_strs[i], 0))
			return (free_split(sub_strs),
				printf("Error\nInvalid char for params\n"), 1);
		xyz[i] = ft_atod(sub_strs[i]);
		i++;
	}
	if (i != 3)
		return (free_split(sub_strs),
			printf("Error\nLess than 3 values for coords/vec\n"), 1);
	if (sub_strs[3] != NULL)
		return (free_split(sub_strs),
			printf("Error\nMore than 3 values for coords/vec\n"), 1);
	free_split(sub_strs);
	return (0);
}
