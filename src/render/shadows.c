/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 21:49:43 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/04 18:31:30 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

//get random number from seed - scrambles bits
// based off of wang_hash
//0xed5ad4bbU = 3981806795
//0xac4c1b51U = 2891336457
//0x31848babU = 830770091
static double	hash_double(unsigned int seed)
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

static unsigned int	build_seed(unsigned int x, unsigned int y,
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

static t_vec3	random_on_unit_disk(unsigned int seed)
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

typedef struct s_shadow_vars
{
	unsigned int	samples;
	int				visible;
	unsigned int	seed;
	double			light_radius;
	unsigned int	i;

	t_vec3			ray_origin;
	t_vec3			to_light;
	t_vec3			disk_normal;
	t_view			disk_view;

	t_vec3			sample;
	t_vec3			sample_pos;
	t_vec3			to_sample;
	double			to_sample_len;

	t_ray			shadow_ray;
	t_hit			shadow_hit;


}	t_shadow_vars;

bool	is_backfacing(t_vec3 normal, t_vec3 point, t_vec3 light_pos)
{
	t_vec3	to_light;
	double	normal_dot_light;

	to_light = vec_subtract(light_pos, point);
	normal_dot_light = vec_dot(normal, to_light);
	return (normal_dot_light <= 0.00);
}

static int	shadow_ray_intersection(t_shadow_vars *v, t_rt *rt)
{
	v->shadow_ray.origin = v->ray_origin;
	v->shadow_ray.dir = vec_normalize(v->to_sample);
	v->shadow_hit = check_intersections_arr(v->shadow_ray, rt);
	if (v->shadow_hit.t <= 0.0 || v->shadow_hit.t >= v->to_sample_len)
		return (1);
	return (0);
}

static void	sample_light(t_shadow_vars *v, t_rt *rt, unsigned int x, unsigned int y)
{
	v->seed = build_seed(x, y, v->i);
	v->sample = random_on_unit_disk(v->seed);
	v->sample_pos = vec_add(rt->scene.light.pos,
			vec_add(vec_scale(v->disk_view.right,
					v->sample.x * v->light_radius),
				vec_scale(v->disk_view.up, v->sample.y * v->light_radius)));
	v->to_sample = vec_subtract(v->sample_pos, v->ray_origin);
	v->to_sample_len = vec_len(v->to_sample);
}


static void set_light_disc_vectors(t_shadow_vars *v, t_rt *rt, t_hit hit)
{
	v->ray_origin = vec_add(hit.point, vec_scale(hit.normal, 1e-4));
	v->to_light = vec_subtract(rt->scene.light.pos, v->ray_origin);
	v->disk_normal = vec_normalize(vec_scale(v->to_light, -1.00));
	v->disk_view = rotate_disk_to_world_view(v->disk_normal);
}

static void init_shadow_vars(t_shadow_vars *v, t_rt *rt)
{
	ft_bzero(v, sizeof(t_shadow_vars));
	v->samples = rt->samples;
	v->i = 0;
	v->light_radius = rt->scene.light.light_radius;
	v->visible = 0;
}

double calc_soft_shadow(t_rt *rt, t_hit hit, unsigned int x, unsigned int y)
{
	t_shadow_vars	v;

	if (is_backfacing(hit.normal, hit.point, rt->scene.light.pos))
		return (0.00);
	init_shadow_vars(&v, rt);
	set_light_disc_vectors(&v, rt, hit);
	while (v.i < v.samples)
	{
		sample_light(&v, rt, x, y);
		if (v.to_sample_len <= 0.0)
		{
			v.i++;
			continue ;
		}
		if (shadow_ray_intersection(&v, rt))
			v.visible++;
		v.i++;
	}
	return ((double)v.visible / (double)v.samples);
}


// double  calc_soft_shadow(t_rt *rt, t_hit hit, unsigned int x, unsigned int y)
// {
// 	unsigned int    samples = rt->samples;
// 	int             visible = 0;
// 	unsigned int    i = 0;
// 	unsigned int    seed;
// 	double          light_radius = 1;//TODO add to light struct

// 	if (is_backfacing(hit.normal, hit.point, rt->scene.light.pos))
// 		return (1.00);
// ////////////////////////////////////////////////////////////////////////////
// 	// place_disc_light and jitter_origin
// 	t_vec3 origin = vec_add(hit.point, vec_scale(hit.normal, 1e-4));
// 	t_vec3 to_light = vec_subtract(rt->scene.light.pos, origin);
// 	t_vec3 disk_normal = vec_normalize(vec_scale(to_light, -1.00));
// 	t_view disk_view = rotate_disk_to_world_view(disk_normal);

// 	while (i < samples)
// 	{
// 		//sample_the_light
// 		seed = build_seed(x, y, i);
// 		t_vec3 sample = random_on_unit_disk(seed);
// 		t_vec3 sample_pos = vec_add(rt->scene.light.pos,
// 			vec_add(vec_scale(disk_view.right, sample.x * light_radius),
// 			vec_scale(disk_view.up, sample.y * light_radius)));
// 		t_vec3 to_sample = vec_subtract(sample_pos, origin);
// 		if (vec_len(to_sample) <= 0.0)
// 		{
// 			i++;
// 			continue;
// 		}
// 		//build a shadow ray
// 		t_ray shadow_ray;
// 		shadow_ray.origin = origin;
// 		shadow_ray.dir = vec_normalize(to_sample);

// 		// t_hit shadow_hit = check_intersections(shadow_ray, rt);
// 		t_hit shadow_hit = check_intersections_arr(shadow_ray, rt);
// 		if (shadow_hit.t <= 0.0 || shadow_hit.t >= vec_len(to_sample))
// 			visible++;
// 		i++;
// 	}
// 	return ((double)visible / (double)samples);
// }

// samples the volume of a sphere
// returns a random vector inside the sphere of size 1;
// t_vec3  random_in_unit_sphere(unsigned int seed)
// {
//     double  x;
//     double  y;
//     double  z;
//     double  r2;
//     t_vec3  result;
	
//     while (1)
//     {
//         // / RAND_MAX to get in range of [0,..,1]
//         // multiply by 2 to extend it to [0,..., 2]
//         // shift -1 so the range is from [-1, ... , 1]
		
//         // // Using Rand leads to lower performance because the threads need to wait for rand
//         // x = 2.0 * ((double)rand() / RAND_MAX) - 1.00;
//         // y = 2.0 * ((double)rand() / RAND_MAX) - 1.00;
//         // z = 2.0 * ((double)rand() / RAND_MAX) - 1.00;
		
	   
//         x = 2.0 * hash_double(seed + 1) - 1.00;
//         y = 2.0 * hash_double(seed + 2) - 1.00;
//         z = 2.0 * hash_double(seed + 3) - 1.00;
	   
//         //check sphere equation x^2 + y^2 + z^2 = r^2
//         r2 = x*x + y*y + z*z;
//         if (r2 > 0.0 && r2 <= 1.0)
//         {
//             result.x = x;
//             result.y = y;
//             result.z = z;
//             return (result);
//         }
//         seed += 0x9E3779B9u;
//     }
// }
// static t_vec3 random_on_unit_sphere(unsigned int seed)
// {
//     double z = 2.0 * hash_double(seed) - 1.0;
//     double a = 2.0 * M_PI * hash_double(seed + 1);
//     double r = sqrt(1.0 - z*z);
//     t_vec3 v = { r * cos(a), r * sin(a), z };
//     return v;
// }