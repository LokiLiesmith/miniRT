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

static t_vec3	vec_rotate_z(t_vec3 v, double angle)
{
	t_vec3	r;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	r.x = v.x * c - v.y * s;
	r.y = v.x * s + v.y * c;
	r.z = v.z;
	return (r);
}

static void rotate_cylinder(t_rt *rt, t_cylinder *cy, t_rot_dir rot_dir, double angle)
{
	(void)rt;
	if (rot_dir == Y_CCW)
		cy->axis = vec_rotate_y(cy->axis, angle);
	if (rot_dir == Y_CW)
		cy->axis = vec_rotate_y(cy->axis, -angle);
	if (rot_dir == X_CCW)
		cy->axis = vec_rotate_x(cy->axis, angle);
	if (rot_dir == X_CW)
		cy->axis = vec_rotate_x(cy->axis, -angle);
	if (rot_dir == Z_CCW)
		cy->axis = vec_rotate_z(cy->axis, angle);
	if (rot_dir == Z_CW)
		cy->axis = vec_rotate_z(cy->axis, -angle);
	cy->axis = vec_normalize(cy->axis);
}

static void rotate_plane(t_rt *rt, t_plane * pl, t_rot_dir rot_dir, double angle)
{
	(void)rt;
	if (rot_dir == Y_CCW)
		pl->normal = vec_rotate_y(pl->normal, angle);
	if (rot_dir == Y_CW)
		pl->normal = vec_rotate_y(pl->normal, -angle);
	if (rot_dir == X_CCW)
		pl->normal = vec_rotate_x(pl->normal, angle);
	if (rot_dir == X_CW)
		pl->normal = vec_rotate_x(pl->normal, -angle);
	if (rot_dir == Z_CCW)
		pl->normal = vec_rotate_z(pl->normal, angle);
	if (rot_dir == Z_CW)
		pl->normal = vec_rotate_z(pl->normal, -angle);
	pl->normal = vec_normalize(pl->normal);
}

static void rotate_object(t_rt *rt, t_object *selected, t_rot_dir rot_dir)
{
	t_object	*obj;
	double		angle;
	
	obj = selected;
	angle = 0.01;
	if (obj->type == SPHERE)
		return ;
	else if (obj->type == CYLINDER)
		rotate_cylinder(rt, (t_cylinder *)obj->data, rot_dir, angle);
	else if (obj->type == PLANE)
		rotate_plane(rt, (t_plane *)obj->data, rot_dir, angle);
	else
		printf("Not a valid object.\n");
	}

static void	rotate_selection(mlx_key_data_t keydata, t_rt *rt)
{

	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		rotate_object(rt, rt->scene.selected, Y_CCW);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		rotate_object(rt, rt->scene.selected, Y_CW);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		rotate_object(rt, rt->scene.selected, X_CCW);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		rotate_object(rt, rt->scene.selected, X_CW);
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		rotate_object(rt, rt->scene.selected, Z_CCW);
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		rotate_object(rt, rt->scene.selected, Z_CW);

}

static void	move_selection(mlx_key_data_t keydata, t_rt *rt)
{
	double speed;

	speed = 1.0;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move_object(rt, rt->scene.selected, speed, LEFT);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move_object(rt, rt->scene.selected, speed, RIGHT);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move_object(rt, rt->scene.selected, speed, UP);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move_object(rt, rt->scene.selected, speed, DOWN);
}

// Esc to close window
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_rt	*rt;
	// double	speed = 1.0;

	rt = (t_rt *)param;
	if (keydata.action != MLX_PRESS)
    	return;
	// OBJECT TRANSLATION
	if (rt->scene.selected)
	{
		if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D ||
				keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S ||
				keydata.key == MLX_KEY_Q || keydata.key == MLX_KEY_E)
			rotate_selection(keydata, rt);
		if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT ||
				keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
			move_selection(keydata, rt);
		if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
			rt->scene.selected = NULL;
	}
	else if (keydata.key == MLX_KEY_ESCAPE)
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
	// if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	// 	rt->scene.camera.dir = vec_rotate_y(rt->scene.camera.dir, -0.05);
	// if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
	// 	rt->scene.camera.dir = vec_rotate_y(rt->scene.camera.dir, 0.05);
	// if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
	// 	rt->scene.camera.dir = vec_rotate_x(rt->scene.camera.dir, -0.05);
	// if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS)
	// 	rt->scene.camera.dir = vec_rotate_x(rt->scene.camera.dir, 0.05);
	rt->samples = 8;
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
		rt->scene.camera.pos = vec_add(rt->scene.camera.pos,
			vec_scale(rt->view.forward, speed));
	else if(ydelta < 0)
		rt->scene.camera.pos = vec_subtract(rt->scene.camera.pos,
			vec_scale(rt->view.forward, speed));
	render(rt);
}
