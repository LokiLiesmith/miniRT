#include "mini_rt.h"

void	print_vec3(t_vec3 v)
{
	printf("(x:%f, y:%f, z:%f)\n", v.x, v.y, v.z);
}

void	print_camera(t_camera cam)
{
	printf("CAMERA\n");
	printf("dir: ");
	print_vec3(cam.dir);
	printf("position: ");
	print_vec3(cam.pos);
	printf("FOV: %f\n", cam.fov);
}
