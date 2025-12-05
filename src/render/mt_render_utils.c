/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_render_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:52:48 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 11:54:04 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
