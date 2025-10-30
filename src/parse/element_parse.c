/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:33:22 by djanardh          #+#    #+#             */
/*   Updated: 2025/10/30 14:04:16 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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

// ambient lighting ratio in the range [0.0,1.0]: 0.2
// R, G, B colors in the range [0-255]: 255, 255, 255
// Ex. A 0.2 255,255,255
int	parse_ambient(char **strs, t_ambient *ambient)
{
	if (!is_valid_double(strs[1], 0))
		return (printf("Error\nInvalid brightness format\n"), 1);
	ambient->brightness = ft_atod(strs[1]);
	if (ambient->brightness < 0.0 || ambient->brightness > 1.0)
		return (printf("Error\nBrightness must be in range [0.0, 1.0]\n"), 1);
	if (parse_rgb(strs[2], ambient->color) != 0)
		return (1);
	return (0);
}

int	parse_camera(char **strs, t_camera *camera)
{
}

int	parse_light(char **strs, t_light *light)
{
}

int	parse_sp(char **strs, t_object *objects)
{
}

int	parse_pl(char **strs, t_object *objects)
{
}

int	parse_cy(char **strs, t_object *objects)
{
}

int	parse_elements(char *line, t_scene *scene)
{
	char	**split_strs;
	int		result;

	result = 1;
	split_strs = ft_split(line, ' ');
	if (!split_strs)
		return (printf("Error\nMemory allocation for ft_split failed\n"), 1);
	if (line[0] == 'A')
		result = parse_ambient(split_strs, &scene->ambient);
	else if (line[0] == 'C')
		result = parse_camera(split_strs, &scene->camera);
	else if (line[0] == 'L')
		result = parse_light(split_strs, &scene->camera);
	else if (line[0] == 's' && line[1] == 'p')
		result = parse_sp(split_strs, &scene->objects);
	else if (line[0] == 'p' && line[1] == 'l')
		result = parse_pl(split_strs, &scene->objects);
	else if (line[0] == 'c' && line[1] == 'y')
		result = parse_cy(split_strs, &scene->objects);
	free_split(split_strs);
	return (result);
}
