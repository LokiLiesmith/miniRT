/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:33:22 by djanardh          #+#    #+#             */
/*   Updated: 2025/10/26 19:16:51 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// add to helper later
int	ft_if_num(char *str)
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
		if (str[count] < '0' || str[count] > '9' || str[count] != '.')
			return (printf("Error\nInvalid char in params\n"), 1);
		count++;
	}
	return (0);
}

// add to helper later
double	ft_atod(char *str)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if  ()
}

// ambient lighting ratio in the range [0.0,1.0]: 0.2
// R, G, B colors in the range [0-255]: 255, 255, 255
// Ex. A 0.2 255,255,255
int	parse_ambient(char **strs, t_ambient *ambient)
{
	char	**rgb;
	// check if all the chars are valid chars i.e, number or .
	// convert to double
	// check limits

	free_split(rgb);
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
