#ifndef THREADS_H
#define THREADS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>

# define WIDTH 100
# define HEIGHT 100
# define MAX_THREADS 32

typedef struct s_rt
{
	int				thread_nr;
	pthread_t		threads[MAX_THREADS];
	pthread_mutex_t	pixel_lock;
	int				current_pixel;
	int				pixel_total;
	//rest of the rt stuff
}	t_rt;



#endif