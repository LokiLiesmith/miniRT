#include	"mini_rt.h"

void	render_pixel(t_rt *rt, int px)
{
	int			x;
	int			y;
	t_ray		ray;
	uint32_t	color;
	t_hit		hit;

	x = px % rt->width;
	y = px / rt->width;
	ray = generate_ray(rt, x, y, rt->view);
	hit = check_intersections(ray, rt);
	if (hit.t > 0)
	{
		color = calculate_color(rt, hit, x, y);
		if (hit.object == rt->scene.selected)
			color = highlight_color(int_to_color(color));
	}
	else
		color = color_scale(rt->scene.ambient.color,
				rt->scene.ambient.brightness);
	// set_pixel(rt->img, x, y, color); // real one
	// for testing without MLX
	set_pixel(rt, x, y, color);
}

void	*routine(void *arg)
{
	int		i;
	int		start;
	int		p;
	t_rt	*rt;

	rt = (t_rt *)arg;
	while (1)
	{
		start = atomic_fetch_add(&rt->a_px_current, 16);
		if (start >= rt->px_total)
			break ;
		i = 0;
		while (i < 16)
		{
			p = start + i;
			if (p >= rt->px_total)
				break ;
			render_pixel_arr(rt, p);
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
// REFACTOR - add safetychecks for threads
void	init_threads(t_rt *rt)
{
	int	i;

	atomic_store(&rt->a_px_current, 0);
	rt->px_current = 0;
	rt->thread_nr = get_thread_count();
	rt->px_total = rt->height * rt->width;
	rt->view = camera_orientation(rt);
	i = 0;
	while (i < rt->thread_nr)
	{//TODO check if thread created == -1?
		pthread_create(&rt->threads[i], NULL, &routine, rt);
		i++;
	}
}
//RECFACTOR - add safetychecks for threads
void	join_threads(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->thread_nr)
	{
		pthread_join(rt->threads[i], NULL);
		i++;
	}
}

void	mt_render(t_rt *rt)
{
	init_threads(rt);
	join_threads(rt);
}

double	get_time_ms(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((ts.tv_sec * 1000.0) + (ts.tv_nsec / 1e6));
}

void	render(t_rt *rt)
{
	double	start;
	double	end;

	start = get_time_ms();
	if (rt->multi_thread == true)
		mt_render(rt);
	else
		st_render(rt);
	end = get_time_ms();
	printf("Render time: %.3f ms\n", end - start);
}
