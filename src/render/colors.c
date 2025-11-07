/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:37:36 by mrazem            #+#    #+#             */
/*   Updated: 2025/11/07 12:20:47 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

uint32_t	rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	uint32_t	color;

	color = r << 24 | g << 16 | b << 8 | a;
	return (color);
}

uint32_t	normal_to_color(t_vec3 normal)
{
    uint8_t r = (uint8_t)((normal.x + 1.0) * 0.5 * 255);
    uint8_t g = (uint8_t)((normal.y + 1.0) * 0.5 * 255);
    uint8_t b = (uint8_t)((normal.z + 1.0) * 0.5 * 255);
    return rgba(r, g, b, 255);
}

uint32_t calculate_color(t_scene scene, t_hit hit, t_camera camera, t_light light)
{
	t_vec3	N = vec_normalize(hit.normal);
	t_vec3	L = vec_normalize(vec_subtract(light.pos, hit.point)); 
	t_vec3	C = vec_normalize(vec_subtract(camera.pos, hit.point));
	t_vec3	R = vec_reflect(vec_scale(L, -1.0), N);
	
	double	intensity;
	double	specular;
	double	diffuse;
	double	ambient;

	ambient = scene.ambient.brightness;
	diffuse = light.brightness * fmax(0.0, vec_dot(N, L));
	specular = light.brightness * pow(fmax(0.0, vec_dot(R, C)), 64.0);
	// combine + clamp
    intensity = ambient + diffuse + specular;
    if (intensity > 1.0)
		intensity = 1.0;
    if (intensity < 0.0)
		intensity = 0.0;

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
