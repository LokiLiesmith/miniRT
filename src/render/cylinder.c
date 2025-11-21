#include "mini_rt.h"


// D_perp^2 * t^2  +   2 * X_perp * D_perp * t + x_perp^2 - r^2;

//a sphere with a component in the N direction ignored = infinite cyl
t_hit	intersect_cylinder(t_ray ray, t_cylinder *cy)
{
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
