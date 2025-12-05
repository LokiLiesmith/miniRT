/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_controls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:54:28 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 13:54:28 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	scale_controls(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_R || keydata.key == MLX_KEY_H
		|| keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
		scale_selection(keydata, rt);
}

static void	rotate_controls(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_D
		|| keydata.key == MLX_KEY_Q || keydata.key == MLX_KEY_E)
		rotate_selection(keydata, rt);
}

static void	move_controls(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_D)
		move_selection(keydata, rt);
}

void	selected_controls(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		rt->mode = MODE_NONE;
		rt->scene.selected = NULL;
		return ;
	}
	if (rt->mode == MODE_NONE)
	{
		set_mode(keydata, rt);
		return ;
	}
	if (rt->mode == MODE_MOVE)
		move_controls(keydata, rt);
	else if (rt->mode == MODE_SCALE)
		scale_controls(keydata, rt);
	else if (rt->mode == MODE_ROTATE)
		rotate_controls(keydata, rt);
}
