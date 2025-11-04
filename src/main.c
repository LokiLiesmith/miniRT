/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:12:25 by djanardh          #+#    #+#             */
/*   Updated: 2025/11/04 18:16:19 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// void	checkleaks(void)
// {
// 	system("leaks miniRT");
// }

int	main(int ac, char **av)
{
	t_rt rt;
	// t_scene scene;

	// atexit(&checkleaks);
	ft_memset(&rt, 0, sizeof(t_rt));
	if (check_input(ac, av, &rt.scene) != 0)
		return (free_objects(&rt.scene.objects), 1);
	// print_scene(&rt.scene);

	// return (free_objects(&rt.scene.objects), 0);

	// mlx things
	rt.mlx = mlx_init(WIDTH, HEIGHT, "Scene1", false);
	if (!rt.mlx)
		return (free_objects(&rt.scene.objects),
			printf("Failed to initialize MLX"), 1);
	rt.img = mlx_new_image(rt.mlx, WIDTH, HEIGHT);
	if (!rt.img)
		return (free_objects(&rt.scene.objects), printf("Failed to create image"),
			1);

	mlx_image_to_window(rt.mlx, rt.img, 0, 0);
	render(&rt);
	mlx_key_hook(rt.mlx, key_hook, &rt);
	mlx_close_hook(rt.mlx, close_hook, &rt);

	mlx_loop(rt.mlx);
	mlx_delete_image(rt.mlx, rt.img);
	mlx_terminate(rt.mlx);
	return (free_objects(&rt.scene.objects), 0);
}