/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:14:01 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 11:14:02 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	resize_update(void *param)
{
	t_rt	*rt;
	double	now;

	rt = param;
	if (!rt->resize_pending)
		return ;
	now = mlx_get_time();
	if (now - rt->last_resize > 0.1)
	{
		mlx_delete_image(rt->mlx, rt->img);
		rt->img = mlx_new_image(rt->mlx, rt->width, rt->height);
		mlx_image_to_window(rt->mlx, rt->img, 0, 0);
		render(rt);
		rt->resize_pending = false;
	}
}

void	on_resize(int32_t width, int32_t height, void *param)
{
	t_rt	*rt;

	rt = param;
	rt->height = height;
	rt->width = width;
	rt->last_resize = mlx_get_time();
	rt->resize_pending = true;
	resize_update(rt);
}
