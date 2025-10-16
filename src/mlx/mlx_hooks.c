/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:10:32 by djanardh          #+#    #+#             */
/*   Updated: 2025/10/16 02:17:05 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// Esc to close window
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(rt->mlx);
	}
///////////////////////////////////////////////////////////////////////
// CAMERA CONTROLS
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.pos.x -= 1;
		render(rt);
		printf("LEFT\n");
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.pos.x += 1;
		render(rt);
		printf("RIGHT\n");
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.pos.y += 1;
		render(rt);
		printf("UP\n");
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.pos.y -= 1;
		render(rt);
		printf("DOWN\n");
	}
// FOV
	if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.fov -= 10;
		render(rt);
		printf("FOV: %f\n", rt->scene.camera.fov);
	}
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.fov += 10;
		render(rt);
		printf("FOV: %f\n", rt->scene.camera.fov);
	}


}

// Close hook to handle window close button
void	close_hook(void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	mlx_close_window(rt->mlx);
}
