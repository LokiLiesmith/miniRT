/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:12:59 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/03 21:26:51 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

typedef struct s_sph_vars
{
	t_vec3	to_sphere;

	double	quad_a;
	double	quad_b;
	double	quad_c;

	double	radius;
	double	discriminant;
	double	t0;
	double	t1;
}	t_sph_vars;

static void	find_roots(t_sph_vars *v, double *t0, double *t1)
{
	double	a;
	double	b;
	double	c;
	double	sqrt_discriminant;

	a = v->quad_a;
	b = v->quad_b;
	c = v->quad_c;
	sqrt_discriminant = sqrt(v->discriminant);
	*t0 = (-b - sqrt_discriminant) / (2 * a);
	*t1 = (-b + sqrt_discriminant) / (2 * a);
}

static void	calc_sph_vars(t_sph_vars *v, t_ray ray, t_sphere *sphere)
{
	v->to_sphere = vec_subtract(ray.origin, sphere->s);
	v->radius = sphere->d * 0.5;
	v->quad_a = vec_dot(ray.dir, ray.dir);
	v->quad_b = 2.0 * vec_dot(ray.dir, v->to_sphere);
	v->quad_c = vec_dot(v->to_sphere, v->to_sphere) - (v->radius * v->radius);
	v->discriminant = v->quad_b * v->quad_b - 4 * v->quad_a * v->quad_c;
}

t_hit	intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_hit		hit;
	t_sph_vars	v;
	double		t0;
	double		t1;

	calc_sph_vars(&v, ray, sphere);
	hit.t = -1.0;
	if (v.discriminant < 0)
		return (hit);
	find_roots(&v, &t0, &t1);
	hit.t = pick_root(t0, t1);
	if (hit.t < 0)
		return (hit);
	hit.point = vec_add(ray.origin, vec_scale(ray.dir, hit.t));
	hit.normal = vec_normalize(vec_subtract(hit.point, sphere->s));
	hit.color = sphere->color;
	inside_check(&hit, ray);
	return (hit);
}

// // D^2 * x^2 + 2 * D (C - S) * t + (C - S)^2 - r^2 = 0;
// // D = ray direction	ray.direction
// // C = Camera(origin)	ray.origin
// // S = Sphere Center	sphere.s
// // r = Sphere radius	sphere.r
// t_hit	intersect_sphere(t_ray ray, t_sphere *sphere)
// {
// 	t_hit	hit;
// 	t_vec3	CS = vec_subtract(ray.origin, sphere->s);
// 	double	r = sphere->d / 2;
// 	double	a = vec_dot(ray.dir, ray.dir);
// 	double	b = 2 * vec_dot(ray.dir, CS);
// 	double	c = vec_dot(CS, CS) - (r * r);
// 	double	discriminant = b * b - (4 * a * c);

// 	//default = no hit
// 	hit.t = -1.00;
// 	if (discriminant < 0.0)
// 		return (hit);

// 	double t0 = (-b - sqrt(discriminant)) / (2 * a);
// 	double t1 = (-b + sqrt(discriminant)) / (2 * a);
// 	double t = -1.0;

// 	//logic for checkin if inside, when we start working with shadows - compare with epsilon cuz 0 isnt exactly 0 anymore (non exact double calculations)
// 	if (t0 > 0)
// 		t = t0;
// 	else if (t0 < 0 && t1 > 0)
// 		t = t1;
// 	else
// 		return (hit);

// 	hit.t = t;
// 	hit.point = vec_add(ray.origin, vec_scale(ray.dir, t));
// 	hit.normal = vec_normalize(vec_subtract(hit.point, sphere->s));
// 	if (vec_dot(ray.dir, hit.normal) > 0)
// 		hit.normal = vec_scale(hit.normal, -1.0);//flip normal if inside
// 	hit.color = sphere->color;
// 	return (hit);
// }
