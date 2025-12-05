/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 22:57:32 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 14:15:23 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_hit	check_intersections(t_ray ray, t_rt *rt)
{
	t_hit		best;
	t_hit		hit;
	t_object	*current;
	double		closest_t;

	best.t = -1.0;
	closest_t = INFINITY;
	current = rt->scene.objects;
	while (current)
	{
		if (current->type == SPHERE)
			hit = intersect_sphere(ray, (t_sphere *)current->data);
		else if (current->type == PLANE)
			hit = intersect_plane(ray, (t_plane *)current->data);
		else if (current->type == CYLINDER)
			hit = intersect_cylinder(ray, (t_cylinder *)current->data);
		if (hit.t > 0.0 && hit.t < closest_t)
		{
			closest_t = hit.t;
			best = hit;
			best.object = current;
		}
		current = current->next;
	}
	return (best);
}

static void	init_mouse_intersect(t_hit *best, double *closest_t, t_rt *rt)
{
	best->t = -1.0;
	best->object = NULL;
	*closest_t = INFINITY;
	rt->scene.selected = NULL;
}

t_hit	check_mouse_intersect(t_ray ray, t_rt *rt)
{
	t_hit		best;
	t_hit		hit;
	t_object	*current;
	double		closest_t;

	init_mouse_intersect(&best, &closest_t, rt);
	current = rt->scene.objects;
	while (current)
	{
		if (current->type == SPHERE)
			hit = intersect_sphere(ray, (t_sphere *)current->data);
		else if (current->type == PLANE)
			hit = intersect_plane(ray, (t_plane *)current->data);
		else if (current->type == CYLINDER)
			hit = intersect_cylinder(ray, (t_cylinder *)current->data);
		if (hit.t > 0.0 && hit.t < closest_t)
		{
			closest_t = hit.t;
			best = hit;
			best.object = current;
		}
		current = current->next;
	}
	rt->scene.selected = best.object;
	return (best);
}
