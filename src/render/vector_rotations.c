#include "mini_rt.h"


typedef struct s_rot_vars
{
	double	c;
	double	s;
	double	dot;
}	t_rot_vars;

//rodrigues rotation around a random vector
// split into perp and paralel and then recalc the fractions in the new plane
// given by the x_product sin for vertical component, cos * perp for horizontal
// add all 3 vectors together and you have your new vector
// v_rot = v_para + (u x v)sin(angle) + cos(theta) * v_perp
t_vec3	vec_rot_around_axis(t_vec3 v, t_vec3 axis, double angle)
{
	t_vec3		u;
	t_vec3		v_para;
	t_vec3		v_perp;
	t_vec3		v_rot;
	t_rot_vars	var;

	u = vec_normalize(axis);
	var.c = cos(angle);
	var.s = sin(angle);
	var.dot = vec_dot(v, u);
	v_para = vec_scale(u, var.dot);
	v_perp = vec_subtract(v, v_para);
	v_rot = vec_add(v_para, vec_add(vec_scale(vec_cross(u, v), var.s),
				vec_scale(v_perp, var.c)));
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