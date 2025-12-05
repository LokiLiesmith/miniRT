/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:09:55 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/05 12:37:26 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	rotate_cylinder(t_rt *rt, t_cylinder *cy, t_rot_dir r_dir, double angle)
{
	if (r_dir == Y_CCW)
		cy->axis = vec_rot_around_axis(cy->axis, rt->view.up, angle);
	if (r_dir == Y_CW)
		cy->axis = vec_rot_around_axis(cy->axis, rt->view.up, -angle);
	if (r_dir == X_CCW)
		cy->axis = vec_rot_around_axis(cy->axis, rt->view.right, angle);
	if (r_dir == X_CW)
		cy->axis = vec_rot_around_axis(cy->axis, rt->view.right, -angle);
	if (r_dir == Z_CCW)
		cy->axis = vec_rot_around_axis(cy->axis, rt->view.forward, angle);
	if (r_dir == Z_CW)
		cy->axis = vec_rot_around_axis(cy->axis, rt->view.forward, -angle);
	cy->axis = vec_normalize(cy->axis);
}

void	rotate_plane(t_rt *rt, t_plane *pl, t_rot_dir r_dir, double angle)
{
	if (r_dir == Y_CCW)
		pl->normal = vec_rot_around_axis(pl->normal, rt->view.up, angle);
	if (r_dir == Y_CW)
		pl->normal = vec_rot_around_axis(pl->normal, rt->view.up, -angle);
	if (r_dir == X_CCW)
		pl->normal = vec_rot_around_axis(pl->normal, rt->view.right, angle);
	if (r_dir == X_CW)
		pl->normal = vec_rot_around_axis(pl->normal, rt->view.right, -angle);
	if (r_dir == Z_CCW)
		pl->normal = vec_rot_around_axis(pl->normal, rt->view.forward, angle);
	if (r_dir == Z_CW)
		pl->normal = vec_rot_around_axis(pl->normal, rt->view.forward, -angle);
	pl->normal = vec_normalize(pl->normal);
}

void	rotate_object(t_rt *rt, t_object *selected, t_rot_dir r_dir)
{
	t_object	*obj;
	double		angle;

	obj = selected;
	angle = 0.03;
	if (obj->type == SPHERE)
		return ;
	else if (obj->type == CYLINDER)
		rotate_cylinder(rt, (t_cylinder *)obj->data, r_dir, angle);
	else if (obj->type == PLANE)
		rotate_plane(rt, (t_plane *)obj->data, r_dir, angle);
	else
		printf("Not a valid object.\n");
}

void	rotate_selection(mlx_key_data_t keydata, t_rt *rt)
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
