/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:15:50 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 13:58:49 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

typedef struct s_intersection_vars
{
	t_hit		best;
	t_hit		hit;
	t_object	*obj;
	t_object	**objects;
	double		closest_t;
	int			i;
	int			count;
}	t_intersection_vars;

static void	init_intersection_vars(t_intersection_vars *v, t_rt *rt)
{
	v->i = 0;
	v->best.t = -1.0;
	v->closest_t = INFINITY;
	v->objects = rt->scene.object_arr;
	v->count = rt->scene.obj_count;
}

t_hit	check_intersections_arr(t_ray ray, t_rt *rt)
{
	t_intersection_vars	v;

	init_intersection_vars(&v, rt);
	while (v.i < v.count)
	{
		v.obj = v.objects[v.i++];
		v.hit.t = -1.00;
		if (v.obj->type == SPHERE)
			v.hit = intersect_sphere(ray, (t_sphere *)v.obj->data);
		if (v.obj->type == PLANE)
			v.hit = intersect_plane(ray, (t_plane *)v.obj->data);
		if (v.obj->type == CYLINDER)
			v.hit = intersect_cylinder(ray, (t_cylinder *)v.obj->data);
		if (v.hit.t > 0.0 && v.hit.t < v.closest_t
			&& v.hit.t < rt->view_distance)
		{
			v.closest_t = v.hit.t;
			v.best = v.hit;
			v.best.object = v.obj;
		}
	}
	return (v.best);
}
// t_hit	check_intersections_arr(t_ray ray, t_rt *rt)
// {
// 	t_intersection_vars v;
//
// 	t_hit		best;
// 	t_hit		hit;
// 	t_object	*obj;
// 	double		closest_t;
// 	int			i;
// 	t_object	**objects;
// 	int			count;
//
// 	i = 0;
// 	best.t = -1.0;
// 	closest_t = INFINITY;
// 	objects = rt->scene.object_arr;
// 	count = rt->scene.obj_count;
//
// 	while (i < count)
// 	{
// 		obj = objects[i++];
// 		hit.t = -1.00;
//
// 		if (obj->type == SPHERE)
// 			hit = intersect_sphere(ray, (t_sphere *)obj->data);
// 		if (obj->type == PLANE)
// 			hit = intersect_plane(ray, (t_plane *)obj->data);
// 		if (obj->type == CYLINDER)
// 			hit = intersect_cylinder(ray, (t_cylinder *)obj->data);
// 		if (hit.t > 0.0 && hit.t < closest_t && hit.t < rt->view_distance)
// 		{
// 			closest_t = hit.t;
// 			best = hit;
// 			best.object = obj;
// 		}
// 	}
// 	return (best);
// }

void	render_pixel_arr(t_rt *rt, int px)
{
	int			x;
	int			y;
	t_ray		ray;
	uint32_t	color;
	t_hit		hit;

	x = px % rt->width;
	y = px / rt->width;
	ray = generate_ray(rt, x, y, rt->view);
	hit = check_intersections_arr(ray, rt);
	if (hit.t > 0)
	{
		color = calculate_color(rt, hit, x, y);
		if (hit.object == rt->scene.selected)
			color = highlight_color(int_to_color(color));
	}
	else
		color = color_scale(rt->scene.ambient.color,
				rt->scene.ambient.brightness);
	set_pixel(rt->img, x, y, color);
}
