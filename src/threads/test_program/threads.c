#include "threads.h"

int	get_thread_count(void);

// void	render_pixel(t_rt *rt, int p)
// {
// 	(void)rt;
// 	printf("%d\n", p);
// }

void	render_pixel(t_rt *rt, int px)
{
	int x;
	int y;
	(void)rt;
	x = px % WIDTH;
	y = px / WIDTH;

	printf("p:%d | x:%d, y:%d\n", px, x, y);

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
		pthread_mutex_lock(&rt->pixel_lock);//SWITCH TO ATOMIC?
		start = rt->current_pixel;
		rt->current_pixel += 16;
		pthread_mutex_unlock(&rt->pixel_lock);
		if (start >= rt->pixel_total)
			break ;
		i = 0;
		while (i < 16)
		{
			p = start + i;
			if (p >= rt->pixel_total)
				break ;
			render_pixel(rt, p);
			i++;
		}
	}
	return (NULL);
}

void	create_threads(t_rt *rt)
{
	int	i;

	rt->thread_nr = get_thread_count();
	rt->pixel_total = WIDTH * HEIGHT;
	if (pthread_mutex_init(&rt->pixel_lock, NULL) != 0)
	{
		printf("Mutex init failed\n");
		return ;
	}
	i = 0;
	while (i < rt->thread_nr)
	{
		pthread_create(&rt->threads[i], NULL, &routine, rt);
		i++;
	}
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
}

int	get_thread_count(void)
{
	int	n;

	n = sysconf(_SC_NPROCESSORS_ONLN);
	if (n < 1)
		n = 1;
	if (n > MAX_THREADS)
		n = MAX_THREADS;
	return (n);
}

int	main(void)
{
	t_rt	rt;

	memset(&rt, 0, sizeof(t_rt));
	create_threads(&rt);
	join_threads(&rt);
	pthread_mutex_destroy(&rt.pixel_lock);
	return (0);
}