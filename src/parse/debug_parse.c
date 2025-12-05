/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:54:20 by djanardh          #+#    #+#             */
/*   Updated: 2025/12/05 15:37:29 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// // Print a vector/point
// void	print_vec3(const char *name, t_vec3 v)
// {
// 	printf("%s: (%.1f, %.1f, %.1f)\n", name, v.x, v.y, v.z);
// }
// 
// // Print color in hex and RGB
// void	print_color(const char *name, t_color color)
// {
// 	printf("%s: (R:%d, G:%d, B:%d)\n", name, color.r, color.g, color.b);
// }
// 
// // Print ambient light
// void	print_ambient(t_ambient *ambient)
// {
// 	printf("\n=== AMBIENT LIGHT ===\n");
// 	printf("Ratio: %.1f\n", ambient->brightness);
// 	print_color("Color", ambient->color);
// }
// 
// // Print camera
// void	print_camera(t_camera *camera)
// {
// 	printf("\n=== CAMERA ===\n");
// 	print_vec3("Position", camera->pos);
// 	print_vec3("Orientation", camera->dir);
// 	printf("FOV: %.1f\n", camera->fov);
// }
// 
// // Print light
// void	print_light(t_light *light)
// {
// 	printf("\n=== LIGHT ===\n");
// 	print_vec3("Position", light->pos);
// 	printf("Brightness: %.1f\n", light->brightness);
// }
// 
// // Print a single object
// void	print_object(t_object *obj, int index)
// {
// 	t_sphere	*sp;
// 	t_plane		*pl;
// 	t_cylinder	*cy;

// 	printf("\n=== OBJECT #%d ===\n", index);
// 	printf("Type: ");
// 	if (obj->type == SPHERE)
// 	{
// 		printf("SPHERE\n");
// 		sp = (t_sphere *)obj->data;
// 		print_vec3("Center", sp->s);
// 		printf("Diameter: %.1f\n", sp->d);
// 		print_color("Color", sp->color);
// 	}
// 	else if (obj->type == PLANE)
// 	{
// 		printf("PLANE\n");
// 		pl = (t_plane *)obj->data;
// 		print_vec3("Point", pl->point);
// 		print_vec3("Normal", pl->normal);
// 		print_color("Color", pl->color);
// 	}
// 	else if (obj->type == CYLINDER)
// 	{
// 		printf("CYLINDER\n");
// 		cy = (t_cylinder *)obj->data;
// 		print_vec3("Center", cy->center);
// 		print_vec3("Axis", cy->axis);
// 		printf("Diameter: %.1f\n", cy->dia);
// 		printf("Height: %.1f\n", cy->height);
// 		print_color("Color", cy->color);
// 	}
// 	else
// 	{
// 		printf("UNKNOWN\n");
// 	}
// }
// 
// // Print all objects in the linked list
// void	print_objects(t_object *objects)
// {
// 	t_object	*current;
// 	int			count;

// 	current = objects;
// 	count = 0;
// 	printf("\n======= OBJECTS =======\n");
// 	if (!current)
// 	{
// 		printf("No objects found.\n");
// 		return ;
// 	}
// 	while (current)
// 	{
// 		print_object(current, count);
// 		current = current->next;
// 		count++;
// 	}
// 	printf("\nTotal objects: %d\n", count);
// }
// 
// // Print the entire scene
// void	print_scene(t_scene *scene)
// {
// 	printf("\n");
// 	printf("╔════════════════════════════════════════╗\n");
// 	printf("║        SCENE PARSING RESULTS           ║\n");
// 	printf("╚════════════════════════════════════════╝\n");
// 	print_ambient(&scene->ambient);
// 	print_camera(&scene->camera);
// 	print_light(&scene->light);
// 	print_objects(scene->objects);
// 	printf("\n");
// 	printf("╔════════════════════════════════════════╗\n");
// 	printf("║           END OF SCENE                 ║\n");
// 	printf("╚════════════════════════════════════════╝\n");
// 	printf("\n");
// }

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
	printf("L %.1f,%.1f,%.1f %.1f\n", l.pos.x, l.pos.y, l.pos.z, l.brightness);
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
