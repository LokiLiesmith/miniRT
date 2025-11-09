#include "mini_rt.h"

void	clear_selection(t_rt *rt)
{
	t_object	*obj;

	obj = rt->scene.objects;
	while (obj)
	{
		obj->selected = false;
		obj = obj->next;
	}
}

void	selected_outline(t_rt *rt)
{

}
