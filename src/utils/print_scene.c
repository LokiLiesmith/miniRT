/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:30:17 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 16:01:06 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	print_save_scene(t_rt *rt)
{
	t_ambient	a;
	t_camera	c;
	t_light		l;

	a = rt->scene.ambient;
	c = rt->scene.camera;
	l = rt->scene.light;
	printf("A %.1f %.d,%.d,%.d\n", a.brightness, a.color.r,
		a.color.g, a.color.b);
	printf("C %.1f,%.1f,%.1f %.1f,%.1f,%.1f %.1f\n",
		c.pos.x, c.pos.y, c.pos.z, c.dir.x, c.dir.y, c.dir.z, c.fov);
	printf("L %.1f,%.1f,%.1f %.1f %d,%d,%d\n",
		l.pos.x, l.pos.y, l.pos.z,
		l.brightness,
		l.color.r, l.color.g, l.color.b);
	print_save_objects(rt);
}

// Print a single object
void	print_save_object(t_object *obj)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	if (obj->type == SPHERE)
	{
		sp = (t_sphere *)obj->data;
		printf("sp %.1f,%.1f,%.1f %.1f %d,%d,%d\n", sp->s.x, sp->s.y,
			sp->s.z, sp->d, sp->color.r, sp->color.g, sp->color.b);
	}
	else if (obj->type == PLANE)
	{
		pl = (t_plane *)obj->data;
		printf("pl %.1f,%.1f,%.1f %.1f,%.1f,%.1f %d,%d,%d\n",
			pl->point.x, pl->point.y, pl->point.z, pl->normal.x,
			pl->normal.y, pl->normal.z, pl->color.r, pl->color.g, pl->color.b);
	}
	else if (obj->type == CYLINDER)
	{
		cy = (t_cylinder *)obj->data;
		printf("cy %.1f,%.1f,%.1f %.7f,%.7f,%.7f %.1f %.1f %d,%d,%d\n",
			cy->center.x, cy->center.y, cy->center.z, cy->axis.x, cy->axis.y,
			cy->axis.z, cy->dia, cy->height,
			cy->color.r, cy->color.g, cy->color.b);
	}
}

void	print_save_objects(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->scene.obj_count)
	{
		print_save_object(rt->scene.object_arr[i]);
		i++;
	}
}
