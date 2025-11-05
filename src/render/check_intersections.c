#include "mini_rt.h"

t_view camera_orientation(t_rt *rt)
{
	t_view	view;

	view.world_up.x = 0;
	view.world_up.y = 1;
	view.world_up.z = 0;

	view.forward = vec_normalize(rt->scene.camera.dir);
	view.right = vec_normalize(vec_cross(view.world_up, view.forward));
	view.up = vec_normalize(vec_cross(view.forward, view.right));
	// print_vec3("forward", view.forward);
	// print_vec3("right", view.right);
	// print_vec3("up", view.up);
	return (view);
}

t_ray	generate_ray(t_rt *rt, int x, int y, t_view view)
{
	t_ray	ray;
	double	fov = rt->scene.camera.fov;
	double	scale = tan((fov * 0.5) * (M_PI/180.0));
	double	aspect_ratio = (double)WIDTH/(double)HEIGHT;
//normalize to [0,1] by dividing with Maximum, +0.5 to move to the middle of the screen
// 2x to stretch the new mapping so when I move -1 we have the interval set at [-1, 1];
	// double u = 2.00 * ((x + 0.5) / (double)WIDTH) - 1.00;
	// double v = 1.00 - 2.00 * ((y + 0.5) / (double)HEIGHT);//same shit but *-1 cuz y starts at the top on screen
	double	u = (2.0 * ((x + 0.5) / (double)WIDTH) - 1.0) * aspect_ratio * scale;
	double	v = (1.0 - 2.0 * ((y + 0.5) / (double)HEIGHT)) * scale;

	t_vec3 dir_cam = {u, v, 1.0};
	// dir_cam = vec_normalize(dir_cam);//NOT NEEDED?
	ray.dir = vec_add(
		vec_add(vec_scale(view.right, dir_cam.x),
				vec_scale(view.up, dir_cam.y)),
		vec_scale(view.forward, dir_cam.z)
	);
	ray.dir = vec_normalize(ray.dir);
	ray.origin = rt->scene.camera.pos;
	return (ray);
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
		hit.t = -1.0;//HOLY MOTHER OF GOD AND ALL THAT IS HOLY
		if (current->type == SPHERE)
			hit = intersect_sphere(ray, (t_sphere *)current->data);
		// else if (current->type == PLANE)
		// 	printf("It's a Plane\n");
		// else if (current->type == CYLINDER)
		// 	printf("It's a Cylinder\n");
	
		if (hit.t > 0.0 && hit.t < closest_t)
		{
			closest_t = hit.t;
			best = hit;
		}
		current = current->next;
	}
	return (best);
}
