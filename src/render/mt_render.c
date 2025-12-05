/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:08:46 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 11:54:33 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	color = set_color(rt, hit, x, y);
	set_pixel(rt->img, x, y, color);
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

void	init_threads(t_rt *rt)
{
	int	i;
	int	j;

	atomic_store(&rt->a_px_current, 0);
	rt->px_current = 0;
	rt->thread_nr = get_thread_count();
	rt->px_total = rt->height * rt->width;
	rt->view = camera_orientation(rt);
	i = 0;
	while (i < rt->thread_nr)
	{
		if (pthread_create(&rt->threads[i], NULL, &routine, rt) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_join(rt->threads[j], NULL);
				j++;
			}
			exit_error(rt, "Failed to create thread");
		}
		i++;
	}
}

void	join_threads(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->thread_nr)
	{
		if (pthread_join(rt->threads[i], NULL) != 0)
		{
			exit_error(rt, "Failed to join thread");
		}
		i++;
	}
}
