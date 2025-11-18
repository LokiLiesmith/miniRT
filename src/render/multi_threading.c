#include	"mini_rt.h"

void	render_pixel(t_rt *rt, int px)
{
	int			x;
	int			y;
	t_ray		ray;
	t_view		view = camera_orientation(rt);
	uint32_t	color;
	t_hit		hit;

	x = px % WIDTH;
	y = px / WIDTH;
	
	ray = generate_ray(rt, x, y, view);
	hit = check_intersections(ray, rt);
	if (hit.t > 0)
	{
		color = calculate_color(rt, hit, x, y);
		if(hit.object == rt->scene.selected)
			color = highlight_color(int_to_color(color));
	}
	else
		color = color_scale(rt->scene.ambient.color, rt->scene.ambient.brightness);
	set_pixel(rt->img, x, y, color);
	// printf("p:%d | x:%d, y:%d\n", px, x, y);
}

void *routine(void *arg)
{
	int	i;
	int	start;
	int	p;
	t_rt	*rt;

	rt = (t_rt *)arg;
	
	while(1)
	{
		// pthread_mutex_lock(&rt->px_lock);
		// start = rt->px_current;
		// rt->px_current += 16;
		// pthread_mutex_unlock(&rt->px_lock);
		start = atomic_fetch_add(&rt->a_px_current, 16);
		if (start >= rt->px_total)
			break ;
		i = 0;
		while (i < 16)
		{
			p = start + i;
			if (p >= rt->px_total)
				break ;
			render_pixel(rt, p);
			i++;
		}
	}
	return (NULL);
}

int	get_thread_count(void)
{
	int	n;

	n = sysconf(_SC_NPROCESSORS_ONLN);
	if (n < 1)
		return (1);
	if (n > MAX_THREADS)
		return (MAX_THREADS);
	return (n);
}

void	init_threads(t_rt *rt)
{
	atomic_store(&rt->a_px_current, 0);
	rt->px_current = 0;
	rt->thread_nr = get_thread_count();
	rt->px_total = WIDTH * HEIGHT;
	int i = 0;
	while (i < rt->thread_nr)
	{
		pthread_create(&rt->threads[i], NULL, &routine, rt);
		i++;
	}
    // printf("Number of Cores: %d\n", rt->thread_nr);
    // printf("MAX_THREADS: %d\n", MAX_THREADS);
	// printf("Init: OK\n");
}
void	join_threads(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->thread_nr)
	{
		pthread_join(rt->threads[i], NULL);
		i++;
	}
	// printf("Join: OK\n");
}

void 	mt_render(t_rt *rt)
{
	init_threads(rt);
	join_threads(rt);
}