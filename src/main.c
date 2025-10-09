#include "mini_rt.h"


// int main(int ac, char **av)
// {
// 	if (ac != 2)
// 		return (print_error*(): use like this and this);
// 	parse_scene();
// 	init_mlx_things();
// 	render_things_and_do_meth();
// 	loop();

// 	return (0);
// }


int main(int ac, char **av)
{
	if (ac != 2)
		return (printf("Usage: './miniRT scene_file.rt'"), 1);
	printf("main online: %s\n", av[1]);
	return (0);
}