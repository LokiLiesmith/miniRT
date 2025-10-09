#include "mini_rt.h"


int main(int ac, char **av)
{
	if (ac != 2)
		return (print error: use like this and this);
	parse_scene();
	init_mlx_things();
	render_things_and_do_meth();
	loop();

	return (0);
}