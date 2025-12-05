/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:14:57 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 13:27:12 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_mouse_data	init_mouse(t_rt *rt)
{
	t_mouse_data	m;

	ft_bzero(&m, sizeof(t_mouse_data));
	mlx_get_mouse_pos(rt->mlx, &m.mx, &m.my);
	m.dx = m.mx - rt->prev_mouse_x;
	m.dy = m.my - rt->prev_mouse_y;
	rt->prev_mouse_x = m.mx;
	rt->prev_mouse_y = m.my;
	return (m);
}

void	drag_loop(void *param)
{
	t_rt			*rt;

	rt = (t_rt *)param;
	if (!rt->pan_drag && !rt->rotate_drag)
		return ;
	if (rt->pan_drag)
		mouse_pan(rt, rt->view);
	else if (rt->rotate_drag)
		mouse_rotate(rt);
	rt->samples = 1;
	render(rt);
}

void	mouse_drag(mouse_key_t btn, action_t action, modifier_key_t mods,
	void *param)
{
	t_rt			*rt;
	t_mouse_data	m;

	rt = (t_rt *)param;
	(void)mods;
	m = init_mouse(rt);
	(void)m;
	if (btn == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		select_object(rt);
	if (btn == MLX_MOUSE_BUTTON_MIDDLE && action == MLX_PRESS)
		rt->pan_drag = true;
	if (btn == MLX_MOUSE_BUTTON_MIDDLE && action == MLX_RELEASE)
		render_on_release(rt, PAN_DRAG);
	if (btn == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		rt->rotate_drag = true;
	if (btn == MLX_MOUSE_BUTTON_RIGHT && action == MLX_RELEASE)
		render_on_release(rt, ROTATE_DRAG);
}

void	mouse_scroll(double xdelta, double ydelta, void *param)
{
	t_rt	*rt;
	double	speed;

	rt = (t_rt *)param;
	speed = 0.5;
	(void)xdelta;
	rt->samples = 1;
	if (ydelta > 0)
		rt->scene.camera.pos = vec_add(rt->scene.camera.pos,
				vec_scale(rt->view.forward, speed));
	else if (ydelta < 0)
		rt->scene.camera.pos = vec_subtract(rt->scene.camera.pos,
				vec_scale(rt->view.forward, speed));
	render(rt);
}
