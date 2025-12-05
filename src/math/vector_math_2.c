/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:33:31 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 11:15:22 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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

t_vec3	vec_reflect(t_vec3 ray_in, t_vec3 normal)
{
	t_vec3	ray_out;
	double	l_dot_n;

	l_dot_n = vec_dot(ray_in, normal);
	ray_out = vec_subtract(ray_in, vec_scale(normal, ((double)2 * l_dot_n)));
	return (ray_out);
}
