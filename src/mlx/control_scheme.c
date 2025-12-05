/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_scheme.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:14:12 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 13:54:41 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

//Set interaction mode when object is selected
void	set_mode(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_G)
	{
		rt->mode = MODE_MOVE;
		printf("MOVE\n");
		return ;
	}
	if (keydata.key == MLX_KEY_S)
	{
		rt->mode = MODE_SCALE;
		rt->scale = SCALE_RADIUS;
		printf("SCALE\n");
		return ;
	}
	if (keydata.key == MLX_KEY_R)
	{
		rt->mode = MODE_ROTATE;
		printf("ROTATE\n");
		return ;
	}
}

void	update_fov(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_EQUAL)
		rt->scene.camera.fov += 10;
	if (keydata.key == MLX_KEY_MINUS)
		rt->scene.camera.fov -= 10;
	printf("FOV:%f\n", rt->scene.camera.fov);
}

void	update_max_distance(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_9)
		rt->view_distance -= 3;
	if (keydata.key == MLX_KEY_0)
		rt->view_distance += 3;
	if (rt->view_distance <= 0)
		rt->view_distance = 3;
}

void	regular_controls(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_N)
	{
		rt->multi_thread = !rt->multi_thread;
		printf("Multi_threading: %d\n", rt->multi_thread);
		render(rt);
	}
	else if (keydata.key == MLX_KEY_0 || keydata.key == MLX_KEY_9)
		update_max_distance(keydata, rt);
	else if (keydata.key == MLX_KEY_M)
	{
		rt->samples = 1024;
		return ;
	}
	else if (keydata.key == MLX_KEY_Z)
		print_save_scene(rt);
	else if (keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_MINUS)
		update_fov(keydata, rt);
	else if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(rt->mlx);
	return ;
}
