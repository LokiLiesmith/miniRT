/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:37:27 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/04 16:57:17 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// for running without MLX for testing
void	set_pixel_headless(uint8_t *buffer, int width, int x, int y, uint32_t color)
{
	int	i;

	i = (y * width + x) * 4;
	buffer[i + 0] = (color >> 24) & 0xFF;	//R
	buffer[i + 1] = (color >> 16) & 0xFF;	//G
	buffer[i + 2] = (color >> 8) & 0xFF;	//B
	buffer[i + 3] = color & 0xFF;			//A
}

void	set_pixel(t_rt *rt, int x, int y, uint32_t color)
{
	int	i;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	
	if (rt->img)  // MLX mode
	{
		i = (y * rt->img->width + x) * 4;
		rt->img->pixels[i + 0] = (color >> 24) & 0xFF;
		rt->img->pixels[i + 1] = (color >> 16) & 0xFF;
		rt->img->pixels[i + 2] = (color >> 8) & 0xFF;
		rt->img->pixels[i + 3] = color & 0xFF;
	}
	else  // Headless mode
	{
		i = (y * WIDTH + x) * 4;
		rt->headless_buffer[i + 0] = (color >> 24) & 0xFF;
		rt->headless_buffer[i + 1] = (color >> 16) & 0xFF;
		rt->headless_buffer[i + 2] = (color >> 8) & 0xFF;
		rt->headless_buffer[i + 3] = color & 0xFF;
	}
}

// this is the real set_pixel()

// void	set_pixel(mlx_image_t *img, int x, int y, uint32_t color)
// {
// 	int	i;

// 	i = (y * img->width + x) * 4;
// 	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
// 		return ;//so we dont go out of bounds
// 	//pixel = RRGGBBAA
// 	img->pixels[i + 0] = (color >> 24) & 0xFF;	//R
// 	img->pixels[i + 1] = (color >> 16) & 0xFF;	//G
// 	img->pixels[i + 2] = (color >> 8) & 0xFF;	//B
// 	img->pixels[i + 3] = color & 0xFF;			//A
// }

// REFACTOR
void	st_render(t_rt *rt)
{
	int			x;
	int			y;
	t_ray		ray;
	uint32_t	color;
	t_hit		hit;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(rt, x, y, rt->view);
			hit = check_intersections(ray, rt);
			if (hit.t > 0)//actual hit
			{
				color = calculate_color(rt, hit, x, y);
				// color = normal_to_color(hit.normal);
				if (hit.object == rt->scene.selected)
					color = highlight_color(int_to_color(color));
			}
			else
				color = color_scale(rt->scene.ambient.color, rt->scene.ambient.brightness);
			// set_pixel(rt->img, x, y, color); // real one
			// fo testing without MLX
			set_pixel(rt, x, y, color);
			x++;
		}
		y++;
	}
}
