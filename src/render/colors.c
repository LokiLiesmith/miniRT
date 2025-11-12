/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:37:36 by mrazem            #+#    #+#             */
/*   Updated: 2025/11/12 06:19:51 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

uint32_t	rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	uint32_t	color;

	color = r << 24 | g << 16 | b << 8 | a;
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
    uint8_t r = (uint8_t)((normal.x + 1.0) * 0.5 * 255);
    uint8_t g = (uint8_t)((normal.y + 1.0) * 0.5 * 255);
    uint8_t b = (uint8_t)((normal.z + 1.0) * 0.5 * 255);
    return rgba(r, g, b, 255);
}

// uint32_t calculate_color(t_scene scene, t_hit hit, t_camera camera, t_light light)
uint32_t calculate_color(t_rt *rt, t_hit hit, unsigned int x, unsigned int y)
{
	t_vec3	N = vec_normalize(hit.normal);
	t_vec3	L = vec_normalize(vec_subtract(rt->scene.light.pos, hit.point)); 
	t_vec3	C = vec_normalize(vec_subtract(rt->scene.camera.pos, hit.point));
	t_vec3	R = vec_reflect(vec_scale(L, -1.0), N);
	
	double	intensity;
	double	specular;
	double	diffuse;
	double	ambient;
	double	visibility;//softshadownumber

	
	ambient = rt->scene.ambient.brightness;
	diffuse = rt->scene.light.brightness * fmax(0.0, vec_dot(N, L));
	specular = rt->scene.light.brightness * pow(fmax(0.0, vec_dot(R, C)), 64.0);
	
	visibility = calc_soft_shadow(rt, hit, x, y);
	//apply visibility
	diffuse *= visibility;
	specular *= visibility;
	// combine + clamp
    intensity = ambient + diffuse + specular;
	uint8_t r = fmin(255.0, hit.color.r * intensity);
	uint8_t g = fmin(255.0, hit.color.g * intensity);
	uint8_t b = fmin(255.0, hit.color.b * intensity);

	// printf("dotNL: %f\n", vec_dot(N, L));
	return (rgba(r, g, b, 255));
}

uint32_t	calculate_shadow(t_scene scene, t_hit shadow_hit)
{
	double	ambient;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	ambient = scene.ambient.brightness;

	r = fmin(255.0, shadow_hit.color.r * ambient);
	g = fmin(255.0, shadow_hit.color.g * ambient);
	b = fmin(255.0, shadow_hit.color.b * ambient);

	return (rgba(r, g, b, 255.0));
}
uint32_t	color_scale(t_color color, double factor)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	r = color.r * factor;
	g = color.g * factor;
	b = color.b * factor;

	return rgba(r, g, b, 255.0);
}

uint32_t	highlight_color(t_color color)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	r = fmin(255, color.r + 80);
	g = fmin(255, color.g + 80);
	b = fmax(0, color.b - 20);

	return (rgba(r, g, b, 255));
}
