/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:01:59 by djanardh          #+#    #+#             */
/*   Updated: 2025/12/03 20:32:04 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_hit	intersect_plane(t_ray ray, t_plane *plane)
{
	t_hit	hit;
	t_vec3	p0o;
	double	a;
	double	b;
	double	t;

	hit.t = -1.0;
	p0o = vec_subtract(plane->point, ray.origin);
	a = vec_dot(plane->normal, ray.dir);
	if (fabs(a) < 1e-6)
		return (hit);
	b = vec_dot(plane->normal, p0o);
	t = b / a;
	if (t <= 0.0)
		return (hit);
	hit.t = t;
	hit.point = vec_add(ray.origin, vec_scale(ray.dir, t));
	hit.normal = plane->normal;
	hit.color = plane->color;
	inside_check(&hit, ray);
	return (hit);
}
