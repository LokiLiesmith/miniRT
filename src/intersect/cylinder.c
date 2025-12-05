/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:18:25 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 14:11:57 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_hit	intersect_cylinder(t_ray ray, t_cylinder *cy)
{
	t_hit	side;
	t_hit	caps;
	t_hit	result;

	side = check_cylinder_side(ray, cy);
	caps = check_caps(ray, cy);
	if (side.t >= 0 && caps.t < 0)
		result = side;
	else if (caps.t >= 0 && side.t < 0)
		result = caps;
	else if (side.t < caps.t)
		result = side;
	else
		result = caps;
	inside_check(&result, ray);
	return (result);
}

// t = (N.(S-O)) / (N.D) = a/b 
t_hit	check_caps(t_ray ray, t_cylinder *cy)
{
	t_hit	t_bot;
	t_hit	t_top;

	t_bot = check_cap(ray, cy, BOT_CAP);
	t_top = check_cap(ray, cy, TOP_CAP);
	if (t_bot.t < 0)
		return (t_top);
	if (t_top.t < 0)
		return (t_bot);
	if (t_bot.t < t_top.t)
		return (t_bot);
	else
		return (t_top);
}

typedef struct s_cap_vars
{
	t_vec3	center;
	t_vec3	to_center;
	double	n_dot_oc;
	double	axis_dot_dir;
	double	radius;
	double	dist_to_center;
}	t_cap_vars;

static void	calc_cap_vars(t_cap_vars *v, t_ray ray, t_cylinder *cy, int cap)
{
	if (cap == TOP_CAP)
		v->center = vec_add(cy->center, vec_scale(cy->axis, cy->height));
	else if (cap == BOT_CAP)
		v->center = cy->center;
	v->to_center = vec_subtract(v->center, ray.origin);
	v->n_dot_oc = vec_dot(cy->axis, v->to_center);
	v->axis_dot_dir = vec_dot(cy->axis, ray.dir);
	v->radius = cy->dia * 0.5;
}

static	void	set_valid_cap_hit(t_hit *hit, t_cylinder *cy, int cap, double t)
{
	hit->t = t;
	hit->color = cy->color;
	if (cap == TOP_CAP)
		hit->normal = cy->axis;
	else if (cap == BOT_CAP)
		hit->normal = vec_scale(cy->axis, -1.0);
}

t_hit	check_cap(t_ray ray, t_cylinder *cy, int cap)
{
	t_hit		hit;
	double		t;
	t_cap_vars	v;

	ft_bzero(&hit, sizeof(t_hit));
	hit.t = -1.00;
	calc_cap_vars(&v, ray, cy, cap);
	if (fabs(v.axis_dot_dir) < 1e-6)
		return (hit);
	t = v.n_dot_oc / v.axis_dot_dir;
	if (t < 0)
		return (hit);
	hit.point = vec_add(ray.origin, vec_scale(ray.dir, t));
	v.dist_to_center = vec_len(vec_subtract(hit.point, v.center));
	if (v.dist_to_center > v.radius)
		return (hit);
	hit.t = t;
	hit.color = cy->color;
	set_valid_cap_hit(&hit, cy, cap, t);
	return (hit);
}
