#include "mini_rt.h"

void	init_vec3(t_vec3 *v, int x, int y, int z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

//vector dot product
double	vec_dot(t_vec3 a, t_vec3 b)
{
	double	res;

	res = (a.x * b.x + a.y * b.y + a.z * b.z);
	return (res);
}

// ()
double	vec_len(t_vec3 v)
{
	double	res;

	res = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (res);
}

//subtract vector2 from vector1
t_vec3	vec_subtract(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vec3	vec_normalize(t_vec3 v)
{
	double	len;

	len = vec_len(v);
	if (len == 0)
		return ((t_vec3){0, 0, 0});
	return ((t_vec3){v.x / len, v.y / len, v.z / len});
}

int	main(void)
{
	t_vec3	a;
	init_vec3(&a, 1, 2, 3);
	print_vec3(a);

	return (0);
}
