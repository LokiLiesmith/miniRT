/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 22:57:32 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 02:21:42 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_view	camera_orientation(t_rt *rt)
{
	t_view	view;
	t_vec3	global_up;
	t_vec3	right_candidate;
	double	len_prev_right;
	double	len_candidate;

	global_up = (t_vec3){0, 1, 0};
	view.forward = vec_normalize(rt->scene.camera.dir);
	right_candidate = vec_cross(global_up, view.forward);
	len_candidate = vec_len(right_candidate);
	if (len_candidate < 1e-6)
	{
		right_candidate = (t_vec3){1, 0, 0};
		len_candidate = 1.0;
	}
	len_prev_right = vec_len(rt->view.right);
	if (len_prev_right > 1e-6)
	{
		if (vec_dot(right_candidate, rt->view.right) < 0.0)
			right_candidate = vec_scale(right_candidate, -1.0);
	}
	view.right = vec_scale(right_candidate, 1.0 / len_candidate);
	view.up = vec_normalize(vec_cross(view.forward, view.right));
	view.world_up = global_up;
	return (view);
}

t_view	rotate_disk_to_world_view(t_vec3 normal)
{
	t_view	view;
	t_vec3	global_up;
	t_vec3	right;

	global_up = (t_vec3){0, 1, 0};
	view.forward = vec_normalize(normal);
	right = vec_cross(global_up, view.forward);
	if (vec_len(right) < 1e-6)
		right = (t_vec3){1, 0, 0};
	view.right = vec_normalize(right);
	view.up = vec_normalize(vec_cross(view.forward, view.right));
	view.world_up = global_up;
	return (view);
}

static t_ray	build_camera_ray(t_view view, t_rt *rt, double u, double v)
{
	t_ray	ray;

	ray.dir = vec_normalize(
			vec_add(
				vec_add(
					vec_scale(view.right, u),
					vec_scale(view.up, v)),
				view.forward));
	ray.origin = rt->scene.camera.pos;
	return (ray);
}

//normalize to [0,1] by dividing with Maximum,
// +0.5 to move to the middle of the screen
// 2x to stretch the new mapping so when
// I move -1 we have the interval set at [-1, 1];
// double u = 2.00 * ((x + 0.5) / (double)WIDTH) - 1.00;
// double v = 1.00 - 2.00 * ((y + 0.5) / (double)HEIGHT);
//same shit but *-1 cuz y starts at the top on screen
t_ray	generate_ray(t_rt *rt, int x, int y, t_view view)
{
	double	scale;
	double	aspect_ratio;
	double	u;
	double	v;

	scale = tan((rt->scene.camera.fov * 0.5) * (M_PI/180.0));
	aspect_ratio = (double)rt->width / (double)rt->height;
	u = (2.0 * ((x + 0.5) / (double)rt->width) - 1.0) * aspect_ratio * scale;
	v = (1.0 - 2.0 * ((y + 0.5) / (double)rt->height)) * scale;
	return (build_camera_ray(view, rt, u, v));
}

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
