/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:10:32 by djanardh          #+#    #+#             */
/*   Updated: 2025/12/05 13:35:02 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (rt->scene.selected)
	{
		rt->samples = rt->prev_samples;
		selected_controls(keydata, rt);
		render(rt);
	}
	else
	{
		rt->prev_samples = rt->samples;
		regular_controls(keydata, rt);
		render(rt);
		rt->samples = rt->prev_samples;
	}
}

// Close hook to handle window close button
void	close_hook(void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	mlx_close_window(rt->mlx);
}
