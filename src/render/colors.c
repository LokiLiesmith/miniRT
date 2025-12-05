/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:37:36 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 02:26:55 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

uint32_t	rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	uint32_t	color;

	color = (uint32_t)r << 24 | (uint32_t)g << 16
		| (uint32_t)b << 8 | (uint32_t)a;
	return (color);
}

t_color	int_to_color(uint32_t color)
{
	t_color	c;

	c.r = (color >> 24) & 0xFF;
	c.g = (color >> 16) & 0xFF;
	c.b = (color >> 8) & 0xFF;

	return (c);
}

uint32_t	normal_to_color(t_vec3 normal)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = (uint8_t)((normal.x + 1.0) * 0.5 * 255);
	g = (uint8_t)((normal.y + 1.0) * 0.5 * 255);
	b = (uint8_t)((normal.z + 1.0) * 0.5 * 255);
	return (rgba(r, g, b, 255));
}


typedef struct s_shade_vars
{
	t_vec3	normal;
	t_vec3	to_light;
	t_vec3	to_camera;
	t_vec3	refl_vec;

	double	intensity;
	double	specular;
	double	diffuse;
	double	ambient;
	double	visibility;
}	t_shade_vars;

void	build_shading_vectors(t_shade_vars *v, t_hit hit, t_rt *rt)
{
	ft_bzero(v, sizeof(t_shade_vars));
	v->normal = vec_normalize(hit.normal);
	v->to_light = vec_normalize(vec_subtract(rt->scene.light.pos, hit.point));
	v->to_camera = vec_normalize(vec_subtract(rt->scene.camera.pos, hit.point));
	v->refl_vec = vec_reflect(vec_scale(v->to_light, -1.00), v->normal);
}

void	calc_light_components(t_shade_vars *v, t_rt *rt)
{
	v->ambient = rt->scene.ambient.brightness;
	v->diffuse = rt->scene.light.brightness * fmax(0.0, vec_dot(v->normal,
				v->to_light));
	v->specular = rt->scene.light.brightness * pow(fmax(0.0,
				vec_dot(v->refl_vec, v->to_camera)), 64.0);
}

static void apply_shadow_visibility(t_shade_vars *v)
{
	v->diffuse *= v->visibility;
	v->specular *= v->visibility;
	v->intensity = v->ambient + v->diffuse + v->specular;
}

uint32_t	calculate_color(t_rt *rt, t_hit hit, unsigned int x, unsigned int y)
{
	t_shade_vars	v;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;

	build_shading_vectors(&v, hit, rt);
	calc_light_components(&v, rt);
	v.visibility = calc_soft_shadow(rt, hit, x, y);
	apply_shadow_visibility(&v);
	r = fmin(255.0, hit.color.r * v.intensity);
	g = fmin(255.0, hit.color.g * v.intensity);
	b = fmin(255.0, hit.color.b * v.intensity);
	return (rgba(r, g, b, 255));
}
// uint32_t calculate_color(t_rt *rt, t_hit hit, unsigned int x, unsigned int y)
// {
// 	t_vec3	N = vec_normalize(hit.normal);
// 	t_vec3	L = vec_normalize(vec_subtract(rt->scene.light.pos, hit.point)); 
// 	t_vec3	C = vec_normalize(vec_subtract(rt->scene.camera.pos, hit.point));
// 	t_vec3	R = vec_reflect(vec_scale(L, -1.0), N);
	
// 	double	intensity;
// 	double	specular;
// 	double	diffuse;
// 	double	ambient;
// 	double	visibility;//softshadownumber

// 	calc_
// 	// rt->scene.ambient.brightness = 0.0;//darkside of the plane
// 	ambient = rt->scene.ambient.brightness;
// 	diffuse = rt->scene.light.brightness * fmax(0.0, vec_dot(N, L));
// 	specular = rt->scene.light.brightness * pow(fmax(0.0, vec_dot(R, C)), 64.0);

// 	visibility = calc_soft_shadow(rt, hit, x, y);
// 	//apply visibility
// 	diffuse *= visibility;
// 	specular *= visibility;
// 	// combine + clamp
//     intensity = ambient + diffuse + specular;
// 	uint8_t r = fmin(255.0, hit.color.r * intensity);
// 	uint8_t g = fmin(255.0, hit.color.g * intensity);
// 	uint8_t b = fmin(255.0, hit.color.b * intensity);
// 	return (rgba(r, g, b, 255));
// }


// uint32_t calculate_color(t_rt *rt, t_hit hit, unsigned int x, unsigned int y)
// {
// 	t_cal_color_vars	v;
// 	init_color_vars(&v, hit, rt);
// }

uint32_t	color_scale(t_color color, double factor)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = color.r * factor;
	g = color.g * factor;
	b = color.b * factor;

	return (rgba(r, g, b, 255.0));
}

uint32_t	highlight_color(t_color color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = fmin(255, color.r + 80);
	g = fmin(255, color.g + 80);
	b = fmax(0, color.b - 20);

	return (rgba(r, g, b, 255));
}
