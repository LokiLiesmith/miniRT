#include "mini_rt.h"

static void	parameter_to_scale(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_H)
		rt->scale = SCALE_HEIGHT;
	else if (keydata.key == MLX_KEY_R)
		rt->scale = SCALE_RADIUS;
}

void scale_cylinder(mlx_key_data_t keydata, t_cylinder *cy, t_scale par)
{
	double	factor;

	factor = 0.1;
	if (par == SCALE_HEIGHT)
	{
		if (keydata.key == MLX_KEY_W)
			cy->height += factor;
		else if (keydata.key == MLX_KEY_S)
			cy->height -= factor;
	}
	else if (par == SCALE_RADIUS)
	{
		if (keydata.key == MLX_KEY_W)
			cy->dia += factor;
		else if (keydata.key == MLX_KEY_S && cy->dia > factor)
			cy->dia -= factor;
	}
}

void scale_sphere(mlx_key_data_t keydata, t_sphere *sp, t_scale par)
{
	double	factor;

	factor = 0.1;
	if (par == SCALE_HEIGHT)
		return ;
	if (par == SCALE_RADIUS)
	{
		if (keydata.key == MLX_KEY_W)
			sp->d += factor;
		else if (keydata.key == MLX_KEY_S && sp->d > factor)
			sp->d -= factor;
	}
}
void scale_selection(mlx_key_data_t keydata, t_rt *rt)
{
	t_object *obj;

	if (keydata.key == MLX_KEY_R || keydata.key == MLX_KEY_H)
	{
		parameter_to_scale(keydata, rt);
		return;
	}
	obj = rt->scene.selected;
	if (obj->type == CYLINDER)
		scale_cylinder(keydata, (t_cylinder *)obj->data, rt->scale);
	else if(obj->type == SPHERE)
		scale_sphere(keydata, (t_sphere *)obj->data, rt->scale);
}
