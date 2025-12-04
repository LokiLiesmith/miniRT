/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:37:27 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/04 19:10:17 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	set_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	i;

	i = (y * img->width + x) * 4;
	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return ;//so we dont go out of bounds
	//pixel = RRGGBBAA
	img->pixels[i + 0] = (color >> 24) & 0xFF;	//R
	img->pixels[i + 1] = (color >> 16) & 0xFF;	//G
	img->pixels[i + 2] = (color >> 8) & 0xFF;	//B
	img->pixels[i + 3] = color & 0xFF;			//A
}

uint32_t	set_color(t_rt *rt, t_hit hit, int x, int y)
{
	uint32_t	color;

	if (hit.t > 0)
	{
		color = calculate_color(rt, hit, x, y);
		if (hit.object == rt->scene.selected)
			color = highlight_color(int_to_color(color));
	}
	else
		color = color_scale(rt->scene.ambient.color,
				rt->scene.ambient.brightness);
	return (color);
}

void	st_render(t_rt *rt)
{
	t_ray		ray;
	uint32_t	color;
	t_hit		hit;
	int			x;
	int			y;

	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			ray = generate_ray(rt, x, y, rt->view);
			hit = check_intersections(ray, rt);
			color = set_color(rt, hit, x, y);
			set_pixel(rt->img, x, y, color);
			x++;
		}
		y++;
	}
}
