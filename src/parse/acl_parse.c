/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:33:22 by djanardh          #+#    #+#             */
/*   Updated: 2025/11/04 16:10:07 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// ambient lighting ratio in the range [0.0,1.0]: 0.2
// R, G, B colors in the range [0-255]: 255, 255, 255
// Ex. A 0.2 255,255,255
int	parse_ambient(char **strs, t_ambient *ambient)
{
	if (!is_valid_double(strs[1], 0))
		return (printf("Error\nInvalid brightness format\n"), 1);
	ambient->brightness = ft_atod(strs[1]);
	if (ambient->brightness < 0.0 || ambient->brightness > 1.0)
		return (printf("Error\nBrightness must be in range [0.0,1.0]\n"), 1);
	if (parse_rgb(strs[2], &ambient->color, 0) != 0)
		return (1);
	return (0);
}

// identifier: C
// x, y, z coordinates of the viewpoint: -50.0,0,20
// 3D normalized orientation vector, in the range [-1,1] for each x, y, z axis:
// 0.0,0.0,1.0
// FOV: Horizontal field of view in degrees in the range [0,180]: 70
int	parse_camera(char **strs, t_camera *camera, int i)
{
	double	xyz[3];

	if (parse_xyz(strs[1], xyz) != 0)
		return (1);
	camera->pos.x = xyz[0];
	camera->pos.y = xyz[1];
	camera->pos.z = xyz[2];
	if (parse_xyz(strs[2], xyz) != 0)
		return (1);
	while (i < 3)
	{
		if (xyz[i] < -1 || xyz[i] > 1)
			return (printf("Error\nC_vec values must be in range [-1,1]\n"), 1);
		i++;
	}
	camera->dir.x = xyz[0];
	camera->dir.y = xyz[1];
	camera->dir.z = xyz[2];
	if (!is_valid_double(strs[3], 0))
		return (printf("Error\nInvalid FOV\n"), 1);
	camera->fov = ft_atod(strs[3]);
	if (camera->fov < 0 || camera->fov > 180)
		return (printf("Error\nFOV must be in range [0,180]\n"), 1);
	return (0);
}

// identifier: L
// x, y, z coordinates of the light point: -40.0,50.0,0.0
// the light brightness ratio in the range [0.0,1.0]: 0.6
int	parse_light(char **strs, t_light *light)
{
	double	xyz[3];

	if (parse_xyz(strs[1], xyz) != 0)
		return (1);
	light->pos.x = xyz[0];
	light->pos.y = xyz[1];
	light->pos.z = xyz[2];
	if (!is_valid_double(strs[2], 0))
		return (printf("Error\nInvalid L_brightness format\n"), 1);
	light->brightness = ft_atod(strs[2]);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		return (printf("Error\nBrightness must be in range [0.0,1.0]\n"), 1);
	return (0);
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
		result = parse_camera(split_strs, &scene->camera, 0);
	else if (line[0] == 'L')
		result = parse_light(split_strs, &scene->light);
	else if (line[0] == 's' && line[1] == 'p')
		result = parse_sp(split_strs, &scene->objects);
	else if (line[0] == 'p' && line[1] == 'l')
		result = parse_pl(split_strs, &scene->objects, 0);
	else if (line[0] == 'c' && line[1] == 'y')
		result = parse_cy(split_strs, &scene->objects, 0);
	free_split(split_strs);
	return (result);
}
