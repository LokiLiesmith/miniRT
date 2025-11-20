/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:10:32 by djanardh          #+#    #+#             */
/*   Updated: 2025/11/18 23:55:37 by mrazem           ###   ########.fr       */
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
	t_view	view;
	double	speed = 1.0;

	rt = (t_rt *)param;
	view = camera_orientation(rt);

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
		// rt->samples = 1024;
		rt->multi_thread = !rt->multi_thread;
		printf("Multi_threading: %d\n", rt->multi_thread);
		render(rt);
		// mt_render(rt);
		return ;
	}
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		rt->samples = 1024;
		render(rt);
		// mt_render(rt);
		return ;
	}
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
	{
		print_save_scene(rt);
		// print_objects(rt->scene.objects);
		return ;
	}	

	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.pos = vec_subtract(rt->scene.camera.pos, vec_scale(view.right, speed));
		printf("LEFT\n");
	}
		if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.pos = vec_add(rt->scene.camera.pos, vec_scale(view.right, speed));
		printf("RIGHT\n");
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.pos = vec_add(rt->scene.camera.pos, vec_scale(view.up, speed));
		printf("UP\n");
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.pos = vec_subtract(rt->scene.camera.pos, vec_scale(view.up, speed));
		printf("DOWN\n");
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
//ROTATION - CAMERA
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.dir = vec_rotate_y(rt->scene.camera.dir, -0.05);
		view = camera_orientation(rt);
	}
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.dir = vec_rotate_y(rt->scene.camera.dir, 0.05);
		view = camera_orientation(rt);
	}
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.dir = vec_rotate_x(rt->scene.camera.dir, -0.05);
		view = camera_orientation(rt);
	}
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.dir = vec_rotate_x(rt->scene.camera.dir, 0.05);
		view = camera_orientation(rt);
	}
	rt->samples = 100;

	// mt_render(rt);
	render(rt);
}
//EXPERIMENTAL - OBJECT SELECTION AND ROTATION
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_rt	*rt;
	int32_t	mx;
	int32_t	my;

	rt = (t_rt *)param;
	mx = 0;
	my = 0;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(rt->mlx, &mx, &my);
		t_ray click_ray = generate_ray(rt, mx, my, camera_orientation(rt));
		t_hit select = check_mouse_intersect(click_ray, rt);
		if(!(select.t > 0))
			rt->scene.selected = NULL;
		else
			print_object(select.object, 1);
		render(rt);
		// mt_render(rt);
	}
}
// Close hook to handle window close button
void	close_hook(void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	mlx_close_window(rt->mlx);
}
