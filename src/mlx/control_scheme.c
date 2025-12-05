#include "mini_rt.h"

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

static void	scale_controls(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_R || keydata.key == MLX_KEY_H
		|| keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
		scale_selection(keydata, rt);
}

static void	rotate_controls(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_D
		|| keydata.key == MLX_KEY_Q || keydata.key == MLX_KEY_E)
		rotate_selection(keydata, rt);
}

static void	move_controls(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_D)
		move_selection(keydata, rt);
}

static void	set_mode(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_G)
	{
		rt->mode = MODE_MOVE;
		printf("MOVE\n");
		return ;
	}
	if (keydata.key == MLX_KEY_S)
	{
		rt->mode = MODE_SCALE;
		rt->scale = SCALE_RADIUS;
		printf("SCALE\n");
		return ;
	}
	if (keydata.key == MLX_KEY_R)
	{
		rt->mode = MODE_ROTATE;
		printf("ROTATE\n");
		return ;
	}
}

static void	selected_controls(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		rt->mode = MODE_NONE;
		rt->scene.selected = NULL;
		return ;
	}
	if (rt->mode == MODE_NONE)
	{
		set_mode(keydata, rt);
		return ;
	}
	if (rt->mode == MODE_MOVE)
		move_controls(keydata, rt);
	else if (rt->mode == MODE_SCALE)
		scale_controls(keydata, rt);
	else if (rt->mode == MODE_ROTATE)
		rotate_controls(keydata, rt);
}

static void	update_fov(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_EQUAL)
		rt->scene.camera.fov += 10;
	if (keydata.key == MLX_KEY_MINUS)
		rt->scene.camera.fov -= 10;
	printf("FOV:%f\n", rt->scene.camera.fov);
}

static void	update_max_distance(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_9)
		rt->view_distance -= 3;
	if (keydata.key == MLX_KEY_0)
		rt->view_distance += 3;
	if (rt->view_distance <= 0)
		rt->view_distance = 3;
}

static void	regular_controls(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_N)
	{
		rt->multi_thread = !rt->multi_thread;
		printf("Multi_threading: %d\n", rt->multi_thread);
		render(rt);
	}
	else if (keydata.key == MLX_KEY_0 || keydata.key == MLX_KEY_9)
		update_max_distance(keydata, rt);
	else if (keydata.key == MLX_KEY_M)
	{
		rt->samples = 1024;
		return ;
	}
	else if (keydata.key == MLX_KEY_Z)
		print_save_scene(rt);
	else if (keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_MINUS)
		update_fov(keydata, rt);
	else if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(rt->mlx);
	return ;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (rt->scene.selected)
	{
		rt->samples = rt->prev_samples;
		selected_controls(keydata, rt);
		render(rt);
	}
	else
	{
		rt->prev_samples = rt->samples;
		regular_controls(keydata, rt);
		render(rt);
		rt->samples = rt->prev_samples;
	}
}
