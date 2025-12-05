/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:00:27 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 14:21:00 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	select_object(t_rt *rt)
{
	int32_t	mx;
	int32_t	my;
	t_ray	click_ray;
	t_hit	select;

	mx = 0;
	my = 0;
	mlx_get_mouse_pos(rt->mlx, &mx, &my);
	click_ray = generate_ray(rt, mx, my, rt->view);
	select = check_mouse_intersect(click_ray, rt);
	if (!(select.t > 0))
	{
		rt->mode = MODE_NONE;
		rt->scene.selected = NULL;
	}
	else
		rt->scene.selected = select.object;
	render(rt);
}

void	render_on_release(t_rt *rt, t_drag_type drag_type)
{
	if (drag_type == PAN_DRAG)
		rt->pan_drag = false;
	else if (drag_type == ROTATE_DRAG)
		rt->rotate_drag = false;
	rt->samples = 100;
	render(rt);
}

void	mouse_pan(t_rt *rt, t_view view)
{
	t_mouse_data	m;
	double			speed;

	m = init_mouse(rt);
	speed = 0.02;
	rt->scene.camera.pos = vec_add(rt->scene.camera.pos,
			vec_add(vec_scale(view.right, speed * -m.dx),
				vec_scale(view.up, speed * m.dy)));
}
// void	mouse_rotate(t_rt *rt, t_view view)
// {
// 	t_mouse_data	m;
// 	double			angle;

// 	(void)view;
// 	m = init_mouse(rt);
// 	angle = 0.0005;
// 	rt->scene.camera.dir = vec_rotate_y(rt->scene.camera.dir, m.dx * -angle);
// 	rt->scene.camera.dir = vec_rotate_x(rt->scene.camera.dir, m.dy * angle);
// 	rt->scene.camera.dir = vec_normalize(rt->scene.camera.dir);
// }

static void	clamp_new_dir_y(t_vec3 *new_dir)
{
	if (new_dir->y > 0.999)
		new_dir->y = 0.999;
	if (new_dir->y < -0.999)
		new_dir->y = -0.999;
}

void	mouse_rotate(t_rt *rt)
{
	t_mouse_data	m;
	double			angle;
	t_view			view;
	t_vec3			global_up;
	t_vec3			new_dir;

	m = init_mouse(rt);
	angle = 0.0005;
	global_up = (t_vec3){0, 1, 0};
	view = camera_orientation(rt);
	if (m.dx != 0)
	{
		rt->scene.camera.dir = vec_rot_around_axis(rt->scene.camera.dir,
				global_up, m.dx * -angle);
	}
	view = camera_orientation(rt);
	if (m.dy != 0)
	{
		new_dir = vec_rot_around_axis(rt->scene.camera.dir,
				view.right, m.dy * -angle);
		clamp_new_dir_y(&new_dir);
		rt->scene.camera.dir = vec_normalize(new_dir);
	}
	rt->view = camera_orientation(rt);
}
