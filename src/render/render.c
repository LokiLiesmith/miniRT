/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:37:27 by mrazem            #+#    #+#             */
/*   Updated: 2025/11/07 11:35:33 by mrazem           ###   ########.fr       */
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

void	render(t_rt *rt)
{
	int			x;
	int			y;
	t_ray		ray;
	t_view		view = camera_orientation(rt);
	uint32_t	color;
	t_hit		hit;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(rt, x, y, view);
			hit = check_intersections(ray, rt);
			if (hit.t > 0)//actual hit
			{
				t_ray shadow_ray;
				t_vec3 light_direction = vec_normalize(vec_subtract(rt->scene.light.pos, hit.point));
				double light_dist = vec_len(vec_subtract(rt->scene.light.pos, hit.point));

				shadow_ray.origin = vec_add(hit.point, vec_scale(hit.normal, 1e-4));
				shadow_ray.dir = light_direction;
				
				t_hit shadow_hit = check_intersections(shadow_ray, rt);
				if (shadow_hit.t > 0 && shadow_hit.t < light_dist)
				{
					color = calculate_shadow(rt->scene, hit);
				}
				else
				{
					color = calculate_color(rt->scene, hit, rt->scene.camera, rt->scene.light);
					// color = normal_to_color(hit.normal);
				}
			}
			else
				color = rgba(255, 255, 255, 255);
			set_pixel(rt->img, x, y, color);
			x++;
		}
		y++;
	}
}
