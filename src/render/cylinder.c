#include "mini_rt.h"

//a sphere with a component in the N direction ignored = infinite cyl
t_hit	intersect_cylinder(t_ray ray, t_cylinder *cy)
{
	t_hit	hit;
	// double	t;
	printf("It's a cylinder!\n");
	(void)ray;
	(void)cy;
	hit.t = 1.00;
	return (hit);
}
