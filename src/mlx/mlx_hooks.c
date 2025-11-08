/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:10:32 by djanardh          #+#    #+#             */
/*   Updated: 2025/11/08 02:24:50 by mrazem           ###   ########.fr       */
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
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(rt->mlx);
	}
///////////////////////////////////////////////////////////////////////
// CAMERA CONTROLS
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.pos = vec_subtract(rt->scene.camera.pos, vec_scale(view.right, speed));
		render(rt);
		printf("LEFT\n");
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.pos = vec_add(rt->scene.camera.pos, vec_scale(view.right, speed));
		render(rt);
		printf("RIGHT\n");
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.pos = vec_add(rt->scene.camera.pos, vec_scale(view.up, speed));
		render(rt);
		printf("UP\n");
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.pos = vec_subtract(rt->scene.camera.pos, vec_scale(view.up, speed));
		render(rt);
		printf("DOWN\n");
	}
// FOV
	if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.fov -= 10;
		render(rt);
		printf("FOV: %f\n", rt->scene.camera.fov);
	}
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.fov += 10;
		render(rt);
		printf("FOV: %f\n", rt->scene.camera.fov);
	}
//ROTATION
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.dir = vec_rotate_y(rt->scene.camera.dir, -0.05);
		view = camera_orientation(rt);
		render(rt);
	}
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
	{

		rt->scene.camera.dir = vec_rotate_y(rt->scene.camera.dir, 0.05);
		view = camera_orientation(rt);
		render(rt);
	}
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
	{
		rt->scene.camera.dir = vec_rotate_x(rt->scene.camera.dir, -0.05);
		view = camera_orientation(rt);
		render(rt);
	}
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS)
	{

		rt->scene.camera.dir = vec_rotate_x(rt->scene.camera.dir, 0.05);
		view = camera_orientation(rt);
		render(rt);
	}
}

// Close hook to handle window close button
void	close_hook(void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	mlx_close_window(rt->mlx);
}
