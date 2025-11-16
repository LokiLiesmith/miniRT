#include "threads.h"

int	get_thread_count(void);


void	render_pixel(t_rt *rt, int p)
{
	(void)rt;
	printf("%d\n", p);
}

void *routine(void *arg)
{
	int i;
	int	start;
	int p;
	t_rt *rt;

	rt = (t_rt *)arg;
	while (1)
	{
		pthread_mutex_lock(&rt->pixel_lock);//SWITCH TO ATOMIC?
		start = rt->current_pixel;
		rt->current_pixel += 16;
		pthread_mutex_unlock(&rt->pixel_lock);
		if(start >= rt->pixel_total)
			break;
		i = 0;
		while (i < 16)
		{
			p = start + i;
			if (p >= rt->pixel_total)
				break;
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
	// printf("N_Cores: %d\n", rt->thread_nr);
	rt->pixel_total = WIDTH * HEIGHT;
	// printf("Pix_tot: %d\n", rt->pixel_total);
	pthread_mutex_init(&rt->pixel_lock, NULL);
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
	i = 9;

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