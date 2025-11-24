#include "mini_rt.h"


t_hit	intersect_cylinder(t_ray ray, t_cylinder *cy)
{
	t_hit	side;
	t_hit	caps;

	side = check_cylinder_side(ray, cy);
	caps = check_caps(ray, cy);

	if (side.t < 0)
		return (caps);
	if (caps.t < 0)
		return (side);
	if (side.t < caps.t)
		return (side);
	else
		return (caps);
}

// D_perp^2 * t^2  +   2 * X_perp * D_perp * t + x_perp^2 - r^2;
//a sphere with a component in the N direction ignored = infinite cyl
t_hit	check_cylinder_side(t_ray ray, t_cylinder *cy)
{
	// cy->axis = vec_normalize(cy->axis);
	t_hit	hit;
	t_vec3	D_para = vec_scale(cy->axis, vec_dot(ray.dir, cy->axis));
	t_vec3	X = vec_subtract(ray.origin, cy->center);
	t_vec3	X_para = vec_scale(cy->axis, vec_dot(X, cy->axis));
	t_vec3	D_perp = vec_subtract(ray.dir, D_para);
	t_vec3	X_perp = vec_subtract(X, X_para);

	double	r = cy->dia/2;

	double	a = vec_dot(D_perp, D_perp);
	double	b = vec_dot(X_perp, D_perp) * 2;
	double	c = vec_dot(X_perp, X_perp) - pow(r, 2);
	double	discriminant = b * b - (4 * a * c);

	hit.t = -1.00;
	if (discriminant < 0.0)
		return (hit);
	
	double t0 = (-b - sqrt(discriminant)) / (2 * a);
	double t1 = (-b + sqrt(discriminant)) / (2 * a);
	double	t = -1.00;

	if (t0 > 0)
		t = t0;
	else if (t0 < 0 && t1 > 0)
		t = t1;
	else
		return (hit);

	hit.t = t;
	hit.point = vec_add(ray.origin, vec_scale(ray.dir, t));
	t_vec3	w = vec_subtract(hit.point, cy->center);
	double h = vec_dot(w, cy->axis);
	t_vec3	w_para = vec_scale(cy->axis ,h);
	t_vec3	w_perp = vec_subtract(w, w_para);
	
	if (h < 0.0 || h > cy->height)
	{
		hit.t = -1.00;
		return (hit);
	}
	hit.normal = vec_normalize(w_perp);
	if (vec_dot(ray.dir, hit.normal) > 0)
		hit.normal = vec_scale(hit.normal, -1.0);//flip normal if inside
	hit.color = cy->color;
	return (hit);
}

// t = (N.(S-O)) / (N.D) = a/b 
t_hit	check_caps(t_ray ray, t_cylinder *cy)
{
	t_hit t_base;
	t_hit t_top;

	t_base = check_base_cap(ray, cy);
	t_top = check_top_cap(ray, cy);

	if (t_base.t < 0)
		return (t_top);
	if (t_top.t < 0)
		return (t_base);
	if (t_base.t < t_top.t)
		return (t_base);
	else
		return (t_top);
}

t_hit	check_top_cap(t_ray ray, t_cylinder *cy)
{
	t_hit hit;
	t_vec3 T = vec_add(cy->center, vec_scale(cy->axis, cy->height));
	t_vec3 SO = vec_subtract(T, ray.origin);
	double a = vec_dot(cy->axis, SO);
	double b = vec_dot(cy->axis, ray.dir);
	double	t;
	t = a / b;
	double 	r = cy->dia / 2;

	hit.t = t;
	hit.point = vec_add(ray.origin, vec_scale(ray.dir, t));
	double len_top = vec_len(vec_subtract(hit.point, vec_add(cy->center, vec_scale(cy->axis, cy->height))));
	if ( len_top <= r)
	{
		hit.t = t;
		hit.normal = cy->axis;
		hit.color = cy->color;
	}
	else hit.t = -1.00;
	return (hit);
}
t_hit	check_base_cap(t_ray ray, t_cylinder *cy)
{
	t_hit hit;
	t_vec3 SO = vec_subtract(cy->center, ray.origin);
	double a = vec_dot(cy->axis, SO);
	double b = vec_dot(cy->axis, ray.dir);
	double	t;
	t = a / b;
	double 	r = cy->dia / 2;

	hit.t = t;
	hit.point = vec_add(ray.origin, vec_scale(ray.dir, t));
	double len_bottom = vec_len(vec_subtract(hit.point, cy->center));
	if ( len_bottom <= r)
	{
		hit.t = t;
		hit.normal = vec_scale(cy->axis, -1.00);
		hit.color = cy->color;
	}
	else hit.t = -1.00;
	return (hit);
}
