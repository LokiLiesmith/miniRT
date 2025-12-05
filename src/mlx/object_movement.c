/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:17:49 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 13:34:46 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	move_sphere(t_rt *rt, t_sphere *sph, double speed, t_mov_dir direction)
{
	t_view	view;

	view = camera_orientation(rt);
	if (direction == LEFT)
		sph->s = vec_subtract(sph->s, vec_scale(view.right, speed));
	if (direction == RIGHT)
		sph->s = vec_add(sph->s, vec_scale(view.right, speed));
	if (direction == UP)
		sph->s = vec_add(sph->s, vec_scale(view.up, speed));
	if (direction == DOWN)
		sph->s = vec_subtract(sph->s, vec_scale(view.up, speed));
}

void	move_plane(t_rt *rt, t_plane *pl, double speed, t_mov_dir dir)
{
	t_view	view;

	view = camera_orientation(rt);
	if (dir == LEFT)
		pl->point = vec_subtract(pl->point, vec_scale(view.right, speed));
	if (dir == RIGHT)
		pl->point = vec_add(pl->point, vec_scale(view.right, speed));
	if (dir == UP)
		pl->point = vec_add(pl->point, vec_scale(view.up, speed));
	if (dir == DOWN)
		pl->point = vec_subtract(pl->point, vec_scale(view.up, speed));
}

void	move_cylinder(t_rt *rt, t_cylinder *cy, double speed, t_mov_dir dir)
{
	t_view	view;

	view = camera_orientation(rt);
	if (dir == LEFT)
		cy->center = vec_subtract(cy->center, vec_scale(view.right, speed));
	if (dir == RIGHT)
		cy->center = vec_add(cy->center, vec_scale(view.right, speed));
	if (dir == UP)
		cy->center = vec_add(cy->center, vec_scale(view.up, speed));
	if (dir == DOWN)
		cy->center = vec_subtract(cy->center, vec_scale(view.up, speed));
}

void	move_object(t_rt *rt, t_object *selected, double speed, t_mov_dir dir)
{
	t_object	*obj;

	obj = selected;
	if (obj->type == SPHERE)
		move_sphere(rt, (t_sphere *)obj->data, speed, dir);
	if (obj->type == PLANE)
		move_plane(rt, (t_plane *)obj->data, speed, dir);
	if (obj->type == CYLINDER)
		move_cylinder(rt, (t_cylinder *)obj->data, speed, dir);
}

void	move_selection(mlx_key_data_t keydata, t_rt *rt)
{
	double	speed;

	speed = 1.0;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_object(rt, rt->scene.selected, speed, LEFT);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_object(rt, rt->scene.selected, speed, RIGHT);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_object(rt, rt->scene.selected, speed, UP);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_object(rt, rt->scene.selected, speed, DOWN);
}
