#ifndef MINI_RT_H
#define MINI_RT_H

#include "structs.h"
# include <stdio.h>


// MLX
//mlx_hooks.c
void	key_hook(mlx_key_data_t keydata, void *param);
void	close_hook(void *param);

// UTILS
//math_utils.c
void print_vec3(t_vec3 v);


#endif