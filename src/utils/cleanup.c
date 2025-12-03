/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 20:39:35 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/03 20:39:36 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	free_all(t_rt *rt)
{
	if (rt->img)
	{
		mlx_delete_image(rt->mlx, rt->img);
		rt->img = NULL;
	}
	if (rt->mlx)
	{
		mlx_terminate(rt->mlx);
		rt->mlx = NULL;
	}
	if (rt->scene.object_arr)
		free_object_arr(&rt->scene);
	if (rt->scene.objects)
		free_objects(&rt->scene.objects);
}

int	exit_error(t_rt *rt, char *msg)
{
	if (msg)
		printf("Error: %s\n", msg);
	free_all(rt);
	exit(EXIT_FAILURE);
}

int	exit_success(t_rt *rt)
{
	free_all(rt);
	exit(EXIT_SUCCESS);
}

void	free_object_arr(t_scene *scene)
{
	free(scene->object_arr);
	scene->object_arr = NULL;
	scene->obj_count = 0;
}

void	free_objects(t_object **list)
{
	t_object	*current;
	t_object	*next;

	if (!list || !*list)
		return ;
	current = *list;
	while (current)
	{
		next = current->next;
		if (current->data)
			free(current->data);
		free(current);
		current = next;
	}
	*list = NULL;
}
