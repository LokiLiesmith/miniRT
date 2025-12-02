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

// TODO REFACTOR
t_hit	check_intersections_arr(t_ray ray, t_rt *rt)
{
	t_hit		best;
	t_hit		hit;
	t_object	*obj;
	double		closest_t;
	int			i;
	t_object	**objs;
	int			count;
	
	i = 0;
	best.t = -1.0;
	closest_t = INFINITY;
	objs = rt->scene.object_arr;
	count = rt->scene.obj_count;

	while (i < count)
	{
		obj = objs[i++];
		hit.t = -1.00;

		if (obj->type == SPHERE)
			hit = intersect_sphere(ray, (t_sphere *)obj->data);
		if (obj->type == PLANE)
			hit = intersect_plane(ray, (t_plane *)obj->data);
		if (obj->type == CYLINDER)
			hit = intersect_cylinder(ray, (t_cylinder *)obj->data);
		if (hit.t > 0.0 && hit.t < closest_t && hit.t < rt->view_distance)
		{
			closest_t = hit.t;
			best = hit;
			best.object = obj;
		}
	}
	return (best);
}

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
