#include "mini_rt.h"


void print_list(t_object *list)
{
	t_object *current;

	current = list;
	while (current)
	{
		if (current->type == SPHERE)
			printf("Type: Sphere\n");
		else if (current->type == PLANE)
			printf("Type: Plane\n");
		else if (current->type == CYLINDER)
			printf("Type: Cylinder\n");

		current = current->next;
	}
}

void	fake_obj_list(t_rt *rt)
{
	t_sphere	*sph_1 = malloc(sizeof(t_sphere));
	t_sphere	*sph_2 = malloc(sizeof(t_sphere));
	t_sphere	*sph_3 = malloc(sizeof(t_sphere));

	sph_1->d = 2;
	sph_1->s.x = 0;
	sph_1->s.y = 0;
	sph_1->s.z = 10;
	sph_1->color.r = 0;
	sph_1->color.g = 160;
	sph_1->color.b = 90;

	sph_2->d = 2;
	sph_2->s.x = 5;
	sph_2->s.y = 0;
	sph_2->s.z = 10;
	sph_2->color.r = 160;
	sph_2->color.g = 240;
	sph_2->color.b = 0;

	sph_3->d = 2;
	sph_3->s.x = 10;
	sph_3->s.y = 0;
	sph_3->s.z = 10;
	sph_3->color.r = 0;
	sph_3->color.g = 160;
	sph_3->color.b = 160;

	add_obj(&rt->scene.objects,create_new_obj(SPHERE, sph_1));
	add_obj(&rt->scene.objects,create_new_obj(SPHERE, sph_2));
	add_obj(&rt->scene.objects,create_new_obj(SPHERE, sph_3));
	print_list(rt->scene.objects);
}

