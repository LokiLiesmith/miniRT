#include "mini_rt.h"


// void    create_threads(t_rt *rt)
// {

// }

// void    assign_jobs(t_rt *rt)
// {

// }

// join_threads()
// {
    
// }
void test_routine(void *arg)
{
	t_thread *a = (t_thread *)arg;
	
	printf("THREAD: %d\n", a->id);
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
	rt->cores = get_thread_count();
	unsigned int i = 0;
	while (i < rt->cores)
	{
		if (pthread_create(rt->threads[i], NULL, test_routine, rt->threads[i].id));
	}
    printf("Number of Cores: %d\n", rt->cores);
    printf("MAX_THREADS: %d\n", MAX_THREADS);
}

int	main(void)
{
    t_rt rt;
    ft_memset(&rt, 0, sizeof(t_rt));

	init_threads(&rt);


    rt.mlx = mlx_init(WIDTH, HEIGHT, "Threads", false);
    rt.img = mlx_new_image(rt.mlx, WIDTH, HEIGHT);
    mlx_image_to_window(rt.mlx, rt.img, 0, 0);
    mlx_close_hook(rt.mlx, close_hook, &rt);
   	mlx_key_hook(rt.mlx, key_hook, &rt);

    mlx_loop(rt.mlx);
    mlx_delete_image(rt.mlx, rt.img);
    mlx_terminate(rt.mlx);

    printf("Threads\n");
	return (0);
}