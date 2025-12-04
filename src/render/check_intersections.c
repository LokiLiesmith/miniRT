#include "mini_rt.h"

t_view	camera_orientation(t_rt *rt)
{
	t_view	view;

	view.world_up.x = 0;
	view.world_up.y = 1;
	view.world_up.z = 0;

	view.forward = vec_normalize(rt->scene.camera.dir);
	if (fabs(view.forward.y) > 0.999)
		view.world_up = (t_vec3){1, 0, 0};
	view.right = vec_normalize(vec_cross(view.world_up, view.forward));
	view.up = vec_normalize(vec_cross(view.forward, view.right));
	return (view);
}

t_view	rotate_disk_to_world_view(t_vec3 normal)
{
	t_view	local_view;

	local_view.world_up.x = 0;
	local_view.world_up.y = 1;
	local_view.world_up.z = 0;

	local_view.forward = vec_normalize(normal);
	if (fabs(local_view.forward.y) > 0.999)
		local_view.world_up = (t_vec3){1, 0, 0};
	local_view.right = vec_normalize(vec_cross(local_view.world_up,
				local_view.forward));
	local_view.up = vec_normalize(vec_cross(local_view.forward,
				local_view.right));
	return (local_view);
}
// //normalize to [0,1] by dividing with Maximum, +0.5 to move to the middle of the screen
// // 2x to stretch the new mapping so when I move -1 we have the interval set at [-1, 1];
// // double u = 2.00 * ((x + 0.5) / (double)WIDTH) - 1.00;
// 	// double v = 1.00 - 2.00 * ((y + 0.5) / (double)HEIGHT);//same shit but *-1 cuz y starts at the top on screen
// t_ray	generate_ray(t_rt *rt, int x, int y, t_view view)
// {
// 	t_ray	ray;
// 	//remap rays based on AR and scale
// 	double	scale = tan((rt->scene.camera.fov * 0.5) * (M_PI/180.0));
// 	double	aspect_ratio = (double)rt->width / (double)rt->height;

// 	//
// 	double	u = (2.0 * ((x + 0.5) / (double)rt->width) - 1.0) * aspect_ratio * scale;
// 	double	v = (1.0 - 2.0 * ((y + 0.5) / (double)rt->height)) * scale;

// 	t_vec3 dir_cam = {u, v, 1.0};
// 	// dir_cam = vec_normalize(dir_cam);//NOT NEEDED?
// 	ray.dir = vec_add(
// 		vec_add(vec_scale(view.right, dir_cam.x),
// 				vec_scale(view.up, dir_cam.y)),
// 		vec_scale(view.forward, dir_cam.z)
// 	);
// 	ray.dir = vec_normalize(ray.dir);
// 	ray.origin = rt->scene.camera.pos;
// 	return (ray);
// }

static t_ray	build_camera_ray(t_view view, t_rt *rt, double u, double v)
{
	t_vec3	img_plane_point;
	t_ray	ray;

	img_plane_point.x = u;
	img_plane_point.y = v;
	img_plane_point.z = 1.0;

	ray.dir = vec_normalize(
			vec_add(
				vec_add(vec_scale(view.right, img_plane_point.x),
					vec_scale(view.up, img_plane_point.y)),
				vec_scale(view.forward, img_plane_point.z)));
	ray.origin = rt->scene.camera.pos;
	return (ray);
}

//normalize to [0,1] by dividing with Maximum, +0.5 to move to the middle of the screen
// 2x to stretch the new mapping so when I move -1 we have the interval set at [-1, 1];
// double u = 2.00 * ((x + 0.5) / (double)WIDTH) - 1.00;
	// double v = 1.00 - 2.00 * ((y + 0.5) / (double)HEIGHT);//same shit but *-1 cuz y starts at the top on screen
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
