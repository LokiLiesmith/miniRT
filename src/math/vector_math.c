/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:33:44 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 11:24:10 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
