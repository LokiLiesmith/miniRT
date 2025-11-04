/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:23:17 by djanardh          #+#    #+#             */
/*   Updated: 2025/11/02 23:08:29 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// identifier: sp
// x, y, z coordinates of the sphere center: 0.0,0.0,20.6
// the sphere diameter: 12.6
// R,G,B colors in the range [0-255]: 10, 0, 255
int	parse_sp(char **strs, t_object **objs_lst)
{
	t_sphere	*sp;
	t_object	*new_obj;
	double		xyz[3];

	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sp)
		return (printf("Error\nsp malloc fail\n"), 1);
	if (parse_xyz(strs[1], xyz) != 0)
		return (free(sp), 1);
	sp->center.x = xyz[0];
	sp->center.y = xyz[1];
	sp->center.z = xyz[2];
	if (!is_valid_double(strs[2], 0))
		return (free(sp), printf("Error\nInvalid sp diameter\n"), 1);
	sp->dia = ft_atod(strs[2]);
	if (sp->dia <= 0.0)
		return (free(sp), printf("Error\nsp dia must be positive\n"), 1);
	if (parse_rgb(strs[3], &sp->color, 0) != 0)
		return (free(sp), 1);
	new_obj = create_new_obj(SPHERE, sp);
	if (!new_obj)
		return (free(sp), 1);
	add_obj(objs_lst, new_obj);
	return (0);
}

// identifier: pl
// x, y, z coordinates of a point in the plane: 0.0,0.0,-10.0
// 3D normalized normal vector, in the range [-1,1] for each x, y, z axis:
// 0.0,1.0,0.0
// R,G,B colors in the range [0-255]: 0,0,225
int	parse_pl_normal(int i, t_plane *pl, double xyz[3])
{
	while (i < 3)
	{
		if (xyz[i] < -1 || xyz[i] > 1)
			return (free(pl),
				printf("Error\npl_vec values must be in range [-1,1]\n"), 1);
		i++;
	}
	pl->normal.x = xyz[0];
	pl->normal.y = xyz[1];
	pl->normal.z = xyz[2];
	return (0);
}

int	parse_pl(char **strs, t_object **objs_lst, int i)
{
	t_plane		*pl;
	t_object	*new_obj;
	double		xyz[3];

	pl = (t_plane *)malloc(sizeof(t_plane));
	if (!pl)
		return (printf("Error\npl malloc fail\n"), 1);
	if (parse_xyz(strs[1], xyz) != 0)
		return (free(pl), 1);
	pl->point.x = xyz[0];
	pl->point.y = xyz[1];
	pl->point.z = xyz[2];
	if (parse_xyz(strs[2], xyz) != 0)
		return (free(pl), 1);
	if (parse_pl_normal(i, pl, xyz) != 0)
		return (free(pl), 1);
	if (parse_rgb(strs[3], &pl->color, 0) != 0)
		return (free(pl), 1);
	new_obj = create_new_obj(PLANE, pl);
	if (!new_obj)
		return (free(pl), 1);
	add_obj(objs_lst, new_obj);
	return (0);
}

// identifier: cy
// x, y, z coordinates of the center of the cylinder: 50.0,0.0,20.6
// 3D normalized vector of axis of cylinder, in the range [-1,1] for each x, y,
// z axis: 0.0,0.0,1.0
// the cylinder diameter: 14.2
// the cylinder height: 21.42
// R, G, B colors in the range [0,255]: 10, 0, 255
int	parse_cy_cont(int i, double xyz[3], char **strs, t_cylinder *cy)
{
	while (i < 3)
	{
		if (xyz[i] < -1 || xyz[i] > 1)
			return (printf("Error\ncy_vec values must be in range [-1,1]\n"),
				1);
		i++;
	}
	cy->axis.x = xyz[0];
	cy->axis.y = xyz[1];
	cy->axis.z = xyz[2];
	if (!is_valid_double(strs[3], 0))
		return (printf("Error\nInvalid cy diameter\n"), 1);
	cy->dia = ft_atod(strs[3]);
	if (cy->dia <= 0.0)
		return (printf("Error\ncy diameter must be positive\n"), 1);
	if (!is_valid_double(strs[4], 0))
		return (printf("Error\nInvalid cy height\n"), 1);
	cy->height = ft_atod(strs[4]);
	if (cy->height <= 0.0)
		return (printf("Error\ncy height must be positive\n"), 1);
	if (parse_rgb(strs[5], &cy->color, 0) != 0)
		return (1);
	return (0);
}

int	parse_cy(char **strs, t_object **objs_lst, int i)
{
	t_cylinder	*cy;
	t_object	*new_obj;
	double		xyz[3];

	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy)
		return (printf("Error\ncy malloc fail\n"), 1);
	if (parse_xyz(strs[1], xyz) != 0)
		return (free(cy), 1);
	cy->center.x = xyz[0];
	cy->center.y = xyz[1];
	cy->center.z = xyz[2];
	if (parse_xyz(strs[2], xyz) != 0)
		return (free(cy), 1);
	if (parse_cy_cont(i, xyz, strs, cy) != 0)
		return (free(cy), 1);
	new_obj = create_new_obj(CYLINDER, cy);
	if (!new_obj)
		return (free(cy), 1);
	add_obj(objs_lst, new_obj);
	return (0);
}
