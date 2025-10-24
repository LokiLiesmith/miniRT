#include "mini_rt.h"

//vector dot product
double	vec_dot(t_vec3 a, t_vec3 b)
{
	double	res;

	res = (a.x * b.x + a.y * b.y + a.z * b.z);
	return (res);
}

// vector length
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

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec3	vec_scale(t_vec3 v, double scale)
{
	t_vec3	res;

	res.x = v.x * scale;
	res.y = v.y * scale;
	res.z = v.z * scale;

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

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;

	return (res);
}
