/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:12:59 by mrazem            #+#    #+#             */
/*   Updated: 2025/11/07 11:53:12 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// D^2 * x^2 + 2 * D (C - S) * t + (C - S)^2 - r^2 = 0;
// D = ray direction	ray.direction
// C = Camera(origin)	ray.origin
// S = Sphere Center	sphere.s
// r = Sphere radius	sphere.r
t_hit	intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_hit	hit;
	t_vec3	CS = vec_subtract(ray.origin, sphere->s);
	double	a = vec_dot(ray.dir, ray.dir);
	double	b = 2 * vec_dot(ray.dir, CS);
	double	c = vec_dot(CS, CS) - (sphere->d * sphere->d);
	double	discriminant = b * b - (4 * a * c);

	//default = no hit
	hit.t = -1.00;
	if (discriminant < 0.0)
		return (hit);

	double t0 = (-b - sqrt(discriminant)) / (2 * a);
	double t1 = (-b + sqrt(discriminant)) / (2 * a);
	double t = -1.0;

	//logic for checkin if inside, when we start working with shadows - compare with epsilon cuz 0 isnt exactly 0 anymore (non exact double calculations)
	if (t0 > 0)
		t = t0;
	else if (t0 < 0 && t1 > 0)
		t = t1;
	else
		return (hit);

	hit.t = t;
	hit.point = vec_add(ray.origin, vec_scale(ray.dir, t));
	hit.normal = vec_normalize(vec_subtract(hit.point, sphere->s));
	if (vec_dot(ray.dir, hit.normal) > 0)
		hit.normal = vec_scale(hit.normal, -1.0);//flip normal if inside
	hit.color = sphere->color;
	return (hit);
}
