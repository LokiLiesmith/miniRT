/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:37:27 by mrazem            #+#    #+#             */
/*   Updated: 2025/11/05 18:37:28 by mrazem           ###   ########.fr       */
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

	print_camera(&rt->scene.camera);

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(rt, x, y, view);
			t_hit hit = check_intersections(ray, rt);
			if (hit.t > 0)
			{
				// uint32_t color = normal_to_color(hit.normal);
				uint32_t color = calculate_color(rt->scene, hit, rt->scene.camera, rt->scene.light);
				// print_vec3(ray.dir);
				set_pixel(rt->img, x, y, color);
			}
			else
				set_pixel(rt->img, x, y, rgba(255, 255, 255, 255));
			// print_vec3(ray.origin);
			// color = trace_ray(ray, scene);
			x++;
		}
		y++;
	}
}
