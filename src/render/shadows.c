/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 21:49:43 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 12:27:08 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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

static int	shadow_ray_intersection(t_shadow_vars *v, t_rt *rt)
{
	v->shadow_ray.origin = v->ray_origin;
	v->shadow_ray.dir = vec_normalize(v->to_sample);
	v->shadow_hit = check_intersections_arr(v->shadow_ray, rt);
	if (v->shadow_hit.t <= 0.0 || v->shadow_hit.t >= v->to_sample_len)
		return (1);
	return (0);
}

static void	sample_light(t_shadow_vars *v, t_rt *rt, unsigned int x,
		unsigned int y)
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

static void	set_light_disc_vectors(t_shadow_vars *v, t_rt *rt, t_hit hit)
{
	v->ray_origin = vec_add(hit.point, vec_scale(hit.normal, 1e-4));
	v->to_light = vec_subtract(rt->scene.light.pos, v->ray_origin);
	v->disk_normal = vec_normalize(vec_scale(v->to_light, -1.00));
	v->disk_view = rotate_disk_to_world_view(v->disk_normal);
}

static void	init_shadow_vars(t_shadow_vars *v, t_rt *rt)
{
	ft_bzero(v, sizeof(t_shadow_vars));
	v->samples = rt->samples;
	v->i = 0;
	v->light_radius = rt->scene.light.light_radius;
	v->visible = 0;
}

double	calc_soft_shadow(t_rt *rt, t_hit hit, unsigned int x, unsigned int y)
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
