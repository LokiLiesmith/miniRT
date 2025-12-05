/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_rendering_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:18:12 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 13:57:32 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	object_arr_len(t_scene *scene)
{
	t_object	*current;

	scene->obj_count = 0;
	current = scene->objects;
	while (current)
	{
		scene->obj_count++;
		current = current->next;
	}
}

static void	normalize_normal(t_object *obj)
{
	t_cylinder	*cy;
	t_plane		*pl;

	if (obj->type == CYLINDER)
	{
		cy = (t_cylinder *)obj->data;
		cy->axis = vec_normalize(cy->axis);
	}
	else if (obj->type == PLANE)
	{
		pl = (t_plane *)obj->data;
		pl->normal = vec_normalize(pl->normal);
	}
}

void	build_object_arr(t_scene *scene)
{
	t_object	*current;
	int			i;

	object_arr_len(scene);
	scene->object_arr = malloc(sizeof(t_object *) * scene->obj_count);
	if (!scene->object_arr)
		exit(1);
	i = 0;
	current = scene->objects;
	while (i < scene->obj_count)
	{
		scene->object_arr[i] = current;
		if (current->type == CYLINDER || current->type == PLANE)
			normalize_normal(current);
		current = current->next;
		i++;
	}
}
