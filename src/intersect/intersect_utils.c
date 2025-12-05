/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:14:35 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 14:30:12 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

//check if hit normal is pointing out
void	inside_check(t_hit *hit, t_ray ray)
{
	if (vec_dot(hit->normal, ray.dir) > 0)
		hit->normal = vec_scale(hit->normal, -1.00);
}

//pick the closest root that is in view
double	pick_root(double t0, double t1)
{
	double	tmp;

	if (t0 > t1)
	{
		tmp = t0;
		t0 = t1;
		t1 = tmp;
	}
	if (t0 > 0)
		return (t0);
	if (t1 > 0)
		return (t1);
	return (-1);
}
