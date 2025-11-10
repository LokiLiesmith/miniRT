#include "mini_rt.h"

// void	clear_selection(t_rt *rt)
// {
// 	t_object	*obj;

// 	obj = rt->scene.objects;
// 	while (obj)
// 	{
// 		if (obj->selected)
// 			obj->selected = false;
// 		obj = obj->next;
// 	}
// }

// void	selected_outline(t_rt *rt)
// {

// }

void	move_sphere(t_rt *rt, t_sphere *sph, double speed, t_mov_dir direction)
{
	t_view view;
	view = camera_orientation(rt);
	if(direction == LEFT)
		sph->s = vec_subtract(sph->s, vec_scale(view.right, speed));
	if(direction == RIGHT)
		sph->s = vec_add(sph->s, vec_scale(view.right, speed));
	if(direction == UP)
		sph->s = vec_add(sph->s, vec_scale(view.up, speed));
	if(direction == DOWN)
		sph->s = vec_subtract(sph->s, vec_scale(view.up, speed));
}

void	move_object(t_rt *rt, t_object *selected, double speed, t_mov_dir direction)
{
	t_object *obj;

	obj = selected;
	if (obj->type == SPHERE)
	{
		t_sphere *sph = (t_sphere *)obj->data;
		move_sphere(rt, sph, speed, direction);
	}
}