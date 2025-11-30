#include "mini_rt.h"
//rodrigues rotation around a random vector
// split into perp and paralel and then recalc the fractions in the new plane
// given by the cross product sin for vertical component, cos * perp for horizontal
// add all 3 vectors together and you have your new vector
t_vec3 vec_rot_around_axis(t_vec3 v, t_vec3 axis, double angle)
{
	t_vec3	u = vec_normalize(axis);
	double	c = cos(angle);
	double	s = sin(angle);
	double 	dot = vec_dot(v, u);
	t_vec3	v_para;
	t_vec3	v_perp;
	t_vec3	v_rot;
	// v_rot = v_para + (u x v)sin(angle) + cos(theta) * v_perp
	v_para = vec_scale(u, dot);
	v_perp = vec_subtract(v, v_para);	
	v_rot = vec_add(v_para, vec_add(vec_scale(vec_cross(u, v), s),
				vec_scale(v_perp, c)));
	return (v_rot);
}

//OBSOLETE - replaced by the general one
t_vec3	vec_rotate_x(t_vec3 v, double angle)
{
	t_vec3	r;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	r.x = v.x;
	r.y = v.y * c - v.z * s;
	r.z = v.y * s + v.z * c;
	return (r);
}

//OBSOLETE - replaced by the general one
t_vec3	vec_rotate_y(t_vec3 v, double angle)
{
	t_vec3	r;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	r.x = v.x * c + v.z * s;
	r.y = v.y;
	r.z = -v.x * s + v.z * c;
	return (r);
}

//OBSOLETE - replaced by the general one
t_vec3	vec_rotate_z(t_vec3 v, double angle)
{
	t_vec3	r;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	r.x = v.x * c - v.y * s;
	r.y = v.x * s + v.y * c;
	r.z = v.z;
	return (r);
}