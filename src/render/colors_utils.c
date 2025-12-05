/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:33:13 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 11:34:14 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
