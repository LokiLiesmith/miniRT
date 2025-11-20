#include "mini_rt.h"

static void	set_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	i;

	i = (y * img->width + x) * 4;

	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return ;//so we dont go out of bounds
	//pixel = RRGGBBAA
	img->pixels[i + 0] = (color >> 24) & 0xFF;	//R
	img->pixels[i + 1] = (color >> 16) & 0xFF;	//G
	img->pixels[i + 2] = (color >> 8) & 0xFF;	//B
	img->pixels[i + 3] = color & 0xFF;			//A
}

static uint32_t	rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	uint32_t	color;

	color = r << 24 | g << 16 | b << 8 | a;
	return (color);
}

uint32_t	normal_to_color(t_vec3 normal)
{
    uint8_t r = (uint8_t)((normal.x + 1.0) * 0.5 * 255);
    uint8_t g = (uint8_t)((normal.y + 1.0) * 0.5 * 255);
    uint8_t b = (uint8_t)((normal.z + 1.0) * 0.5 * 255);
    return rgba(r, g, b, 255);
}

static t_ray	generate_ray(t_rt *rt, int x, int y, t_view view)
// static t_ray generate_ray(t_vec3 origin, int x, int y)
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

// D^2 * x^2 + 2 * D (C - S) * t + (C - S)^2 - r^2 = 0;
// D = ray direction	ray.direction
// C = Camera(origin)	ray.origin
// S = Sphere Center	sphere.s
// r = Sphere radius	sphere.r
t_hit	intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_hit	hit;
	t_vec3	CS = vec_subtract(ray.origin, sphere->s);
	double	a = vec_dot(ray.dir, ray.dir);
	double	b = 2 * vec_dot(ray.dir, CS);
	double	c = vec_dot(CS, CS) - ((sphere->d / 2) * (sphere->d / 2));
	double	discriminant = b * b - (4 * a * c);

	//default = no hit
	hit.t = -1.00;
	if (discriminant < 0.0)
		return (hit);

	double t0 = (-b - sqrt(discriminant)) / (2 * a);
	double t1 = (-b + sqrt(discriminant)) / (2 * a);
	double t = -1.0;

	//logic for checkin if inside, when we start working with shadows - compare with epsilon cuy 0 isnt exactly 0 anymore
	if (t0 > 0.0)
		t = t0;
	else if (t0 < 0 && t1 > 0)
		t = t1;
	else
		return (hit);

	hit.t = t;
	hit.point = vec_add(ray.origin, vec_scale(ray.dir, t));
	hit.normal = vec_normalize(vec_subtract(hit.point, sphere->s));
	if(vec_dot(ray.dir, hit.normal) > 0)
		hit.normal = vec_scale(hit.normal, -1.0);//flip normal if inside
	hit.color = sphere->color;
	return (hit);
}

t_view camera_orientation(t_rt *rt)
{
	t_view	view;

	view.world_up.x = 0;
	view.world_up.y = 1;
	view.world_up.z = 0;

	view.forward = vec_normalize(rt->scene.camera.dir);
	view.right = vec_normalize(vec_cross(view.world_up, view.forward));
	view.up = vec_normalize(vec_cross(view.forward, view.right));
	// print_vec3(view.forward);
	// print_vec3(view.right);
	// print_vec3(view.up);
	return (view);
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
		else if (current->type == PLANE)
			printf("It's a Plane\n");
		else if (current->type == CYLINDER)
			printf("It's a Cylinder\n");
	
		if (hit.t > 0.0 && hit.t < closest_t)
		{
			closest_t = hit.t;
			best = hit;
		}
		current = current->next;
	}
	return (best);
}

uint32_t calculate_color(t_scene scene, t_hit hit, t_camera camera, t_light light)
{
	t_vec3	N = vec_normalize(hit.normal);
	t_vec3	L = vec_normalize(vec_subtract(light.pos, hit.point)); 
	t_vec3	C = vec_normalize(vec_subtract(camera.pos, hit.point));
	t_vec3	R = vec_reflect(vec_scale(L, -1.0), N);
	
	double	intensity;
	double	specular;
	double	diffuse;
	double	ambient;

	ambient = scene.ambient.brightness;
	diffuse = light.brightness * fmax(0.0, vec_dot(N, L));
	specular = light.brightness * pow(fmax(0.0, vec_dot(R, C)), 64.0);
	// combine + clamp
    intensity = ambient + diffuse + specular;
    if (intensity > 1.0)
		intensity = 1.0;
    if (intensity < 0.0)
		intensity = 0.0;

	uint8_t r = fmin(255.0, hit.color.r * intensity);
	uint8_t g = fmin(255.0, hit.color.g * intensity);
	uint8_t b = fmin(255.0, hit.color.b * intensity);

	// printf("dotNL: %f\n", vec_dot(N, L));
	return (rgba(r, g, b, 255));
}

void	render(t_rt *rt)
{
	int			x;
	int			y;
	t_ray		ray;
	// t_vec3		origin = rt->scene.camera.pos;
	// t_sphere	sphere_2;
	t_view		view = camera_orientation(rt);

	// print_camera(rt->scene.camera);

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(rt, x, y, view);
			t_hit hit = check_intersections(ray, rt);
			if (hit.t > 0)
			{
				// uint32_t color = normal_to_color(hit.normal);
				uint32_t color = calculate_color(rt->scene, hit, rt->scene.camera, rt->scene.light);
				// print_vec3(ray.dir);
				set_pixel(rt->img, x, y, color);
			}
			else
				set_pixel(rt->img, x, y, rgba(255, 255, 255, 255));
			// print_vec3(ray.origin);
			// color = trace_ray(ray, scene);
			x++;
		}
		y++;
	}
}

// static void	fake_parsing(t_rt *rt)
// {
// //CAMERA
// 	rt->scene.camera.pos.x = 0;
// 	rt->scene.camera.pos.y = 0;
// 	rt->scene.camera.pos.z = 0;
	
// 	rt->scene.camera.fov = 70.00;
	
// 	rt->scene.camera.dir.x = 0;
// 	rt->scene.camera.dir.y = 0;
// 	rt->scene.camera.dir.z = 1;
// //AMBIENT
// 	rt->scene.ambient.brightness = 0.2;
// 	rt->scene.ambient.color.r = 255;
// 	rt->scene.ambient.color.g = 255;
// 	rt->scene.ambient.color.b = 255;
// //LIGHT
// 	rt->scene.light.pos.x = -50;
// 	rt->scene.light.pos.y = 0;
// 	rt->scene.light.pos.z = 5;

// 	rt->scene.light.brightness = 0.7;

// 	rt->scene.light.color.r = 255;
// 	rt->scene.light.color.g = 255;
// 	rt->scene.light.color.b = 255;

// 	print_camera(rt->scene.camera);
	
// 	// rt->s
// //OBJECTS
// 	fake_obj_list(rt);
// }
// static uint32_t calculate_color(point)
// {
// 	i = Ispec + Ideff + Iambient;
// 	Ispec = dot(reflect, ray_that_hit_the_point);
// 	color = rgba(r * i, g * i, b * i, 255);
// 	return color;
// }



// int	main(int ac, char **av)
// {
// 	t_rt	rt;

// 	if (ac != 2)
// 		return (printf("Usage: './miniRT scene_file.rt'\n"), 1);
// 	printf("main online: %s\n", av[1]);

// 	rt.mlx = mlx_init(WIDTH, HEIGHT, "Scene1", false);
// 	if (!rt.mlx)
// 		return (printf("Failed to initialize MLX"), 1);
// 	rt.img = mlx_new_image(rt.mlx, WIDTH, HEIGHT);
// 	if (!rt.img)
// 		return (printf("Failed to create image"), 1);
// 	//TESTING///////////////////////////////////////////////////////////////
// 	fake_parsing(&rt);//TESTING STRUCT
// 	////////////////////////////////////////////////////////////////////////
	
// 	mlx_image_to_window(rt.mlx, rt.img, 0, 0);
// 	render(&rt);
// 	mlx_key_hook(rt.mlx, key_hook, &rt);
// 	mlx_close_hook(rt.mlx, close_hook, &rt);
// 	mlx_loop(rt.mlx);
// 	mlx_delete_image(rt.mlx, rt.img);
// 	mlx_terminate(rt.mlx);

// 	return (0);
// }

