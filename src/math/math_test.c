#include "mini_rt.h"

void init_vec3(t_vec3 *v, int x, int y, int z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}
void print_vec3(t_vec3 v)
{
	printf("(x:%f, y:%f, z:%f)\n", v.x, v.y, v.z);
}


int	main(void)
{
	t_vec3 a;
	init_vec3(&a, 1, 2, 3);
	print_vec3(a);

	return (0);
}