/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:03:46 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 14:30:01 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

typedef struct s_side_vars
{
	t_vec3	d_para;
	t_vec3	d_perp;
	t_vec3	x_vec;
	t_vec3	x_para;
	t_vec3	x_perp;

	double	radius;
	double	quad_a;
	double	quad_b;
	double	quad_c;
	double	discriminant;

	t_vec3	hit_vec;
	t_vec3	hit_para;
	t_vec3	hit_perp;
	double	h_on_axis;
}	t_side_vars;

// D_perp^2 * t^2  +   2 * X_perp * D_perp * t + x_perp^2 - r^2;
static void	calc_side_vars(t_side_vars *v, t_ray ray, t_cylinder *cy)
{
	v->x_vec = vec_subtract(ray.origin, cy->center);
	v->d_para = vec_scale(cy->axis, vec_dot(ray.dir, cy->axis));
	v->x_para = vec_scale(cy->axis, vec_dot(v->x_vec, cy->axis));
	v->d_perp = vec_subtract(ray.dir, v->d_para);
	v->x_perp = vec_subtract(v->x_vec, v->x_para);
	v->radius = cy->dia * 0.5;
	v->quad_a = vec_dot(v->d_perp, v->d_perp);
	v->quad_b = 2.0 * vec_dot(v->x_perp, v->d_perp);
	v->quad_c = vec_dot(v->x_perp, v->x_perp) - (v->radius * v->radius);
	v->discriminant = v->quad_b * v->quad_b - 4 * v->quad_a * v->quad_c;
}

//find roots of the quadratic equation -- CYLINDER VARS
static void	find_roots(t_side_vars *v, double *t0, double *t1)
{
	double	a;
	double	b;
	double	sqrt_discriminant;

	a = v->quad_a;
	b = v->quad_b;
	sqrt_discriminant = sqrt(v->discriminant);
	*t0 = (-b - sqrt_discriminant) / (2 * a);
	*t1 = (-b + sqrt_discriminant) / (2 * a);
}

//calculate hit projection on the axis and decompose hit vector
static void	calc_axis_and_hit_vec(t_side_vars *v, t_hit hit, t_cylinder *cy)
{
	v->hit_vec = vec_subtract(hit.point, cy->center);
	v->h_on_axis = vec_dot(v->hit_vec, cy->axis);
	v->hit_para = vec_scale(cy->axis, v->h_on_axis);
	v->hit_perp = vec_subtract(v->hit_vec, v->hit_para);
}

// D_perp^2 * t^2  +   2 * X_perp * D_perp * t + x_perp^2 - r^2;
//a sphere with a component in the N direction ignored = infinite cyl
t_hit	check_cylinder_side(t_ray ray, t_cylinder *cy)
{
	t_hit		hit;
	t_side_vars	v;
	double		t0;
	double		t1;

	calc_side_vars(&v, ray, cy);
	hit.t = -1.00;
	if (v.discriminant < 0.0)
		return (hit);
	find_roots(&v, &t0, &t1);
	hit.t = pick_root(t0, t1);
	if (hit.t < 0)
		return (hit);
	hit.point = vec_add(ray.origin, vec_scale(ray.dir, hit.t));
	calc_axis_and_hit_vec(&v, hit, cy);
	if (v.h_on_axis < 0.0 || v.h_on_axis > cy->height)
		return (hit.t = -1.00, hit);
	hit.normal = vec_normalize(v.hit_perp);
	hit.color = cy->color;
	return (hit);
}
