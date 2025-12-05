/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:12:25 by djanardh          #+#    #+#             */
/*   Updated: 2025/12/05 02:22:37 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	main_loop(void *param)
{
	t_rt	*rt;

	rt = param;
	drag_loop(rt);
	resize_update(rt);
}

static void	init_hooks(t_rt *rt)
{
	mlx_key_hook(rt->mlx, key_hook, rt);
	mlx_scroll_hook(rt->mlx, mouse_scroll, rt);
	mlx_mouse_hook(rt->mlx, mouse_drag, rt);
	mlx_resize_hook(rt->mlx, on_resize, rt);
	mlx_close_hook(rt->mlx, close_hook, rt);
	mlx_loop_hook(rt->mlx, main_loop, rt);
}

static int	init_rt(t_rt *rt)
{
	ft_memset(rt, 0, sizeof(t_rt));
	rt->samples = 8;
	rt->prev_samples = 8;
	rt->multi_thread = true;
	rt->width = WIDTH;
	rt->height = HEIGHT;
	rt->resize_pending = false;
	rt->view_distance = MAX_DISTANCE;
	rt->scene.light.light_radius = 1;
	return (0);
}

static int	init_graphics(t_rt *rt)
{
	rt->mlx = mlx_init(rt->width, rt->height, "MiniRT", true);
	if (!rt->mlx)
		return (-1);
	rt->img = mlx_new_image(rt->mlx, rt->width, rt->height);
	if (!rt->img)
		return (-1);
	if (mlx_image_to_window(rt->mlx, rt->img, 0, 0) == -1)
		return (-1);
	init_hooks(rt);
	return (0);
}

int	main(int ac, char **av)
{
	t_rt	rt;

	if (init_rt(&rt) == -1)
		exit_error(&rt, "Init_rt failed");
	if (check_input(ac, av, &rt.scene) != 0)
		exit_error(&rt, "Bad input");
	build_object_arr(&rt.scene);
	if (init_graphics(&rt) == -1)
		exit_error(&rt, "graphics init failed");
	render(&rt);
	mlx_loop(rt.mlx);
	return (exit_success(&rt));
}
