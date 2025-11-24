/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:10:32 by djanardh          #+#    #+#             */
/*   Updated: 2025/11/24 20:59:09 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_vec3	vec_rotate_x(t_vec3 v, double angle)
{
	t_vec3	r;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	r.x = v.x;
	r.y = v.y * c - v.z * s;
	r.z = v.y * s + v.z * c;
	return (r);
}

static t_vec3	vec_rotate_y(t_vec3 v, double angle)
{
	t_vec3	r;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	r.x = v.x * c + v.z * s;
	r.y = v.y;
	r.z = -v.x * s + v.z * c;
	return (r);
}

// Esc to close window
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_rt	*rt;
	double	speed = 1.0;

	rt = (t_rt *)param;
	if (keydata.action != MLX_PRESS)
    	return;
	// OBJECT TRANSLATION
	if (rt->scene.selected)
	{
		if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
			move_object(rt, rt->scene.selected, speed, LEFT);
		if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
			move_object(rt, rt->scene.selected, speed, RIGHT);
		if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
			move_object(rt, rt->scene.selected, speed, UP);
		if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
			move_object(rt, rt->scene.selected, speed, DOWN);
		if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
			rt->scene.selected = NULL;
	}
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS && !rt->scene.selected)
	{
		mlx_close_window(rt->mlx);
		return ;
	}
///////////////////////////////////////////////////////////////////////
// CAMERA CONTROLS
	if (keydata.key == MLX_KEY_N && keydata.action == MLX_PRESS)
	{
		rt->multi_thread = !rt->multi_thread;
		printf("Multi_threading: %d\n", rt->multi_thread);
		render(rt);
		return ;
	}
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		rt->samples = 1024;
		render(rt);
		return ;
	}
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
	{
		print_save_scene(rt);
		return ;
	}	
// FOV
	if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.fov -= 10;
		printf("FOV: %f\n", rt->scene.camera.fov);
	}
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.fov += 10;
		printf("FOV: %f\n", rt->scene.camera.fov);
	}
//ROTATION - CAMERA ////KEEEP FOR OBJECT ROTATION??? TODO
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		rt->scene.camera.dir = vec_rotate_y(rt->scene.camera.dir, -0.05);
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		rt->scene.camera.dir = vec_rotate_y(rt->scene.camera.dir, 0.05);
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
		rt->scene.camera.dir = vec_rotate_x(rt->scene.camera.dir, -0.05);
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS)
		rt->scene.camera.dir = vec_rotate_x(rt->scene.camera.dir, 0.05);
	rt->samples = 100;
	render(rt);
}

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
		rt->scene.selected = NULL;
	else
		rt->scene.selected = select.object;
	render(rt);
}

static t_mouse_data	init_mouse(t_rt *rt)
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

static	void render_on_release(t_rt *rt, t_drag_type drag_type)
{
	if (drag_type == PAN_DRAG)
		rt->pan_drag = false;
	else if (drag_type == ROTATE_DRAG)
		rt->rotate_drag = false;
	rt->samples = 100;
	render(rt);
}

//EXPERIMENTAL - OBJECT SELECTION AND ROTATION
void	mouse_drag(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_rt			*rt;
	t_mouse_data	m;

	rt = (t_rt *)param;
	(void)mods;
	m = init_mouse(rt);
	(void)m;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		select_object(rt);
	if (button == MLX_MOUSE_BUTTON_MIDDLE && action == MLX_PRESS)
		rt->pan_drag = true;
	if (button == MLX_MOUSE_BUTTON_MIDDLE && action == MLX_RELEASE)
		render_on_release(rt, PAN_DRAG);
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		rt->rotate_drag = true;
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_RELEASE)
		render_on_release(rt, ROTATE_DRAG);
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

void	mouse_rotate(t_rt *rt, t_view view)
{
	t_mouse_data	m;
	double			angle;

	(void)view;
	m = init_mouse(rt);
	angle = 0.0005;

	rt->scene.camera.dir = vec_rotate_y(rt->scene.camera.dir, m.dx * angle);
	rt->scene.camera.dir = vec_rotate_x(rt->scene.camera.dir, m.dy * angle);
	rt->scene.camera.dir = vec_normalize(rt->scene.camera.dir);
}

void	drag_loop(void *param)
{
	t_rt			*rt;
	t_view			view;

	rt = (t_rt *)param;
	view = camera_orientation(rt);
	if (!rt->pan_drag && !rt->rotate_drag)
		return ;
	if (rt->pan_drag)
		mouse_pan(rt, view);
	else if (rt->rotate_drag)
		mouse_rotate(rt, view);
	rt->samples = 1;
	render(rt);
}

// Close hook to handle window close button
void	close_hook(void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	mlx_close_window(rt->mlx);
}

void	mouse_scroll(double xdelta, double ydelta, void *param)
{
	t_rt	*rt;
	double	speed;

	rt = (t_rt *)param;
	speed = 0.5;
	(void)xdelta;
	rt->samples = 1;
	if(ydelta > 0)
		rt->scene.camera.pos = vec_add(rt->scene.camera.pos, vec_scale(rt->view.forward, speed));
	else if(ydelta < 0)
		rt->scene.camera.pos = vec_subtract(rt->scene.camera.pos, vec_scale(rt->view.forward, speed));
	render(rt);
}
