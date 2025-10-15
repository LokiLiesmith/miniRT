#include "mini_rt.h"


static void	set_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	i;

	i = (y * img->width + x) * 4;

	if ( x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
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

static t_ray generate_ray(t_vec3 origin, int x, int y)
{
    t_ray	ray;
	// double	fov = 150.0;
	// double	fov = 90.0;
	double	fov = 70.0;
	// double	fov = 30.0;
	double	scale = tan((fov * 0.5) * (M_PI/180.0));
	double	aspect_ratio = WIDTH/HEIGHT;
//normalize to [0,1] by dividing with Maximum, +0.5 to move to the middle of the screen
// 2x to stretch the new mapping so when I move -1 we have the interval set at [-1, 1];
	double u = 2.00 * ((x + 0.5) / (double)WIDTH) - 1.00;
	double v = 1.00 - 2.00 * ((y + 0.5) / (double)HEIGHT);//same shit but *-1 cuz y starts at the top on screen

	ray.dir.x = u * scale * aspect_ratio;
	ray.dir.y = v * scale;//scale is new max based on the FOV/2.. tan(FOV/2)
	ray.dir.z = 1;

	ray.dir = vec_normalize(ray.dir);

	ray.origin = origin;
	return (ray);
}



// D^2 * x^2 + 2 * D (C - S) * t + (C - S)^2 - r^2 = 0;
// D = ray direction	ray.direction
// C = Camera(origin)	ray.origin
// S = Sphere Center	sphere.s
// r = Sphere radius	sphere.r
int	check_intersection(t_ray ray, t_sphere sphere)
{
	t_vec3	CS = vec_subtract(ray.origin, sphere.s);
	float	a = vec_dot(ray.dir, ray.dir);
	float	b = 2 * vec_dot(ray.dir, CS);
	float	c = vec_dot(CS, CS) - (sphere.r * sphere.r);

	float	discriminant = b * b - (4 * a * c);
	if (discriminant < 0)
		return (0);
	return (1);
}

void	render(t_rt *rt)
{
	int			x;
	int			y;
	t_ray		ray;
	// uint32_t	color;
	t_vec3		origin = {0, 0, -20};
	t_sphere	sphere;

	sphere.r = 5;
	sphere.s.x = 7;
	sphere.s.y = 2;
	sphere.s.z = 0;
	
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(origin, x, y);
			float hit = check_intersection(ray, sphere);
			if (hit)
			{
				print_vec3(ray.dir);
				set_pixel(rt->img, x, y, rgba(0, 255, 255, 255));
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

int	main(int ac, char **av)
{
	t_rt rt;

	if (ac != 2)
		return (printf("Usage: './miniRT scene_file.rt'\n"), 1);
	printf("main online: %s\n", av[1]);

	rt.mlx = mlx_init(WIDTH, HEIGHT, "Scene1", false);
	if (!rt.mlx)
		return (printf("Failed to initialize MLX"), 1);
	rt.img = mlx_new_image(rt.mlx, WIDTH, HEIGHT);
	if (!rt.img)
			return (printf("Failed to create image"), 1);
	mlx_image_to_window(rt.mlx, rt.img, 0, 0);
	render(&rt);
	mlx_key_hook(rt.mlx, key_hook, &rt);
	mlx_close_hook(rt.mlx, close_hook, &rt);
	mlx_loop(rt.mlx);
	mlx_delete_image(rt.mlx, rt.img);
	mlx_terminate(rt.mlx);

	return (0);
}
