/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:12:25 by djanardh          #+#    #+#             */
/*   Updated: 2025/12/04 18:59:42 by djanardh         ###   ########.fr       */
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

static void	main_loop(void *param)
{
	t_rt	*rt;

	rt = param;
	drag_loop(rt);
	resize_update(rt);
}

static void	init_hooks(t_rt *rt)
{
	mlx_key_hook(rt->mlx, key_hook, rt);
	mlx_scroll_hook(rt->mlx, mouse_scroll, rt);
	mlx_mouse_hook(rt->mlx, mouse_drag, rt);
	mlx_resize_hook(rt->mlx, on_resize, rt);
	mlx_close_hook(rt->mlx, close_hook, rt);
	mlx_loop_hook(rt->mlx, main_loop, rt);
}

static int	init_rt(t_rt *rt)
{
	ft_memset(rt, 0, sizeof(t_rt));
	rt->samples = 8;
	rt->prev_samples = 8;
	rt->multi_thread = true;
	rt->width = WIDTH;
	rt->height = HEIGHT;
	rt->resize_pending = false;
	rt->view_distance = MAX_DISTANCE;
	rt->scene.light.light_radius = 1;
	return (0);
}

static int	init_graphics(t_rt *rt)
{
	rt->mlx = mlx_init(rt->width, rt->height, "MiniRT", true);
	if (!rt->mlx)
		return (-1);
	rt->img = mlx_new_image(rt->mlx, rt->width, rt->height);
	if (!rt->img)
		return (-1);
	if (mlx_image_to_window(rt->mlx, rt->img, 0, 0) == -1)
		return (-1);
	init_hooks(rt);
	return (0);
}

// real main:
// int	main(int ac, char **av)
// {
// 	t_rt	rt;

// 	if (init_rt(&rt) == -1)
// 		exit_error(&rt, "Init_rt failed");
// 	if (check_input(ac, av, &rt.scene) != 0)
// 		exit_error(&rt, "Bad input");
// 	build_object_arr(&rt.scene);
// 	if (init_graphics(&rt) == -1)
// 		exit_error(&rt, "graphics init failed");
// 	render(&rt);
// 	mlx_loop(rt.mlx);
// 	return (exit_success(&rt));
// }

// HEADLESS: main for testing without MLX
int	main(int ac, char **av)
{
	t_rt	rt;

	if (ac > 2 && strcmp(av[2], "--headless") == 0)
		rt.headless = true;
	else
		rt.headless = false;

	printf("Headless mode: %s\n", rt.headless ? "YES" : "NO"); 
		
	if (init_rt(&rt) == -1)
		exit_error(&rt, "Init_rt failed");
	if (ac > 2 && strcmp(av[2], "--headless") == 0)
		rt.headless = true;
	else
		rt.headless = false;
	check_input(ac, av, &rt.scene);
		// exit_error(&rt, "Bad input");
	build_object_arr(&rt.scene);
	
	if (!rt.headless)
	{
		if (init_graphics(&rt) == -1)
			exit_error(&rt, "graphics init failed");
	}
	else
	{
		printf("SKIPPING GRAPHICS INIT - HEADLESS MODE\n");  // ADD THIS
		rt.headless_buffer = malloc(WIDTH * HEIGHT * 4);
		if (!rt.headless_buffer)
			exit_error(&rt, "malloc failed");
		rt.img = NULL;
		rt.mlx = NULL;  // ADD THIS - make sure MLX is NULL
	}
	
	render(&rt);
	
	if (!rt.headless)
	{
		printf("CALLING MLX_LOOP\n");
		mlx_loop(rt.mlx);
	}
	else
	{
		printf("SKIPPING MLX_LOOP - Headless render complete\n");
		free(rt.headless_buffer);
	}
	return (exit_success(&rt));
}

// int	main(int ac, char **av)
// {
// 	t_rt	rt;

// 	init_rt(&rt);
// 	if (check_input(ac, av, &rt.scene) != 0)
// 		return (free_objects(&rt.scene.objects), 1);
// 	rt.mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
// 	if (!rt.mlx)
// 		return (free_objects(&rt.scene.objects),
// 			printf("Failed to initialize MLX"), 1);
// 	rt.img = mlx_new_image(rt.mlx, WIDTH, HEIGHT);
// 	if (!rt.img)
// 		return (free_objects(&rt.scene.objects),
// 			printf("Failed to create image"), 1);
// 	build_object_arr(&rt.scene);
// 	mlx_image_to_window(rt.mlx, rt.img, 0, 0);
// 	render(&rt);
// 	init_hooks(&rt);
// 	mlx_loop(rt.mlx);
// 	mlx_delete_image(rt.mlx, rt.img);
// 	mlx_terminate(rt.mlx);
// 	free_object_arr(&rt.scene); //TODO: free LL and ARRAY together?
// 	return (free_objects(&rt.scene.objects), 0);
// }