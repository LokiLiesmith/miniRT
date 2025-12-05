/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:02:09 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 12:27:03 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	is_backfacing(t_vec3 normal, t_vec3 point, t_vec3 light_pos)
{
	t_vec3	to_light;
	double	normal_dot_light;

	to_light = vec_subtract(light_pos, point);
	normal_dot_light = vec_dot(normal, to_light);
	return (normal_dot_light <= 0.00);
}
