/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:56:28 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 13:41:31 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

//get random number from seed - scrambles bits
double	hash_double(unsigned int seed)
{
	seed ^= seed >> 17;
	seed *= 0xed5ad4bbU;
	seed ^= seed >> 11;
	seed *= 0xac4c1b51U;
	seed ^= seed >> 15;
	seed *= 0x31848babU;
	seed ^= seed >> 14;
	return ((seed & 0xFFFFFFu) / (double)0x1000000u);
}
// based off of wang_hash
//0xed5ad4bbU = 3981806795
//0xac4c1b51U = 2891336457
//0x31848babU = 830770091
// 
// double wang_hash(uint32_t x)
// {
//     x ^= 61U;//U for unsigned so it wraps
//     x ^= x >> 16;//shift 16 and XOR
//     x += x << 3;
//     x ^= x >> 4;
//     x *= 0x27d4eb2dU;
//     x ^= x >> 15;

//     return((x & 0xFFFFFFu) / (double)0x1000000u);
// }

unsigned int	build_seed(unsigned int x, unsigned int y,
									unsigned int sample_id)
{
	unsigned int	s;

	s = 0;
	s ^= x * 73856093u;
	s ^= y * 19349663u;
	s ^= sample_id * 83492791u;
	if (s == 0)
		s = 1;
	return (s);
}

t_vec3	random_on_unit_disk(unsigned int seed)
{
	t_vec3	random;
	double	u1;
	double	u2;
	double	r;
	double	theta;

	u1 = hash_double(seed);
	u2 = hash_double(seed + 1);
	r = sqrt(u1);
	theta = 2 * M_PI * u2;
	random.x = r * cos(theta);
	random.y = r * sin(theta);
	random.z = 0.0;
	return (random);
}

t_view	rotate_disk_to_world_view(t_vec3 normal)
{
	t_view	view;
	t_vec3	global_up;
	t_vec3	right;

	global_up = (t_vec3){0, 1, 0};
	view.forward = vec_normalize(normal);
	right = vec_cross(global_up, view.forward);
	if (vec_len(right) < 1e-6)
		right = (t_vec3){1, 0, 0};
	view.right = vec_normalize(right);
	view.up = vec_normalize(vec_cross(view.forward, view.right));
	view.world_up = global_up;
	return (view);
}
