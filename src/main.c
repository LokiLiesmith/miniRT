/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:12:25 by djanardh          #+#    #+#             */
/*   Updated: 2025/10/11 20:15:11 by djanardh         ###   ########.fr       */
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


int main(int ac, char **av)
{
	t_rt rt;

	if (ac != 2)
		return (printf("Usage: './miniRT scene_file.rt'\n"), 1);
	printf("main online: %s\n", av[1]);

	// mlx things
	rt.mlx = mlx_init(WIDTH, HEIGHT, "Scene1", false);
	if (!rt.mlx)
		return (printf("Failed to initialize MLX"), 1);
	rt.img = mlx_new_image(rt.mlx, WIDTH, HEIGHT);
	if (!rt.img)
			return (printf("Failed to create image"), 1);
	mlx_image_to_window(rt.mlx, rt.img, 0, 0);
	mlx_key_hook(rt.mlx, key_hook, &rt);
	mlx_close_hook(rt.mlx, close_hook, &rt);
	mlx_loop(rt.mlx);
	mlx_delete_image(rt.mlx, rt.img);
	mlx_terminate(rt.mlx);

	return (0);
}
