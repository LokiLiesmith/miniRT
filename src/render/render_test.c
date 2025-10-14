#include "mini_rt.h"


static void set_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	int i;

	i = (y * img->width + x) * 4;

	if ( x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return ;//so we dont go out of bounds
	//pixel = RRGGBBAA
	img->pixels[i + 0] = (color >> 24) & 0xFF;//R
	img->pixels[i + 1] = (color >> 16) & 0xFF;//G
	img->pixels[i + 2] = (color >> 8) & 0xFF;//B
	img->pixels[i + 3] = color & 0xFF;//A

}

static uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	uint32_t color;

	color = r << 24 | g << 16 | b << 8 | a;
	return color;
}

static t_ray	generate_ray(t_vec3 origin, int x, int y)
{
	t_ray	ray;

	ray.dir.x = x;
	ray.dir.y = y;
	ray.dir.z = 0;
	ray.origin.x = origin.x;
	ray.origin.y = origin.y;
	ray.origin.z = origin.z;

	return (ray);
}

int	check_intersection(t_ray ray, t_sphere sphere)
{
	float	D;
	4D^2(C-S)^2  -  4D^2(C-S) 
	if D < 0 no hits;
	
	return (0)
}

void render(t_rt *rt)
{
	int			x;
	int 		y;
	t_ray		ray;
	// uint32_t	color;
	t_vec3		origin = {0,0,-20};
	t_sphere	sphere;

	sphere.r = 20;
	sphere.s.x = 0;
	sphere.s.y = 0;
	sphere.s.z = 20;
	
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(origin, x, y);
			if (!check_intersection(ray, sphere))
				set_pixel(rt->img, x, y, rgba(0, 255, 255 , 255));

			// print_vec3(ray.dir);
			// print_vec3(ray.origin);
			// color = trace_ray(ray, scene);
			x++;
		}
		y++;
	}
}








int main(int ac, char **av)
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
