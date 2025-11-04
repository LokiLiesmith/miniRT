/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:36:17 by mrazem            #+#    #+#             */
/*   Updated: 2025/11/04 00:54:10 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "structs.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "../include/libft/libft.h"

//MATH
double	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
t_vec3	vec_subtract(t_vec3 a, t_vec3 b);
double	vec_len(t_vec3 v);
t_vec3	vec_normalize(t_vec3 v);
t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 v, double scale);
t_vec3	vec_reflect(t_vec3 ray_in, t_vec3 normal);

//RENDER
void        render(t_rt *rt);
uint32_t	normal_to_color(t_vec3 normal);
uint32_t    calculate_color(t_scene scene, t_hit hit, t_camera camera, t_light light);




// MLX
//mlx_hooks.c
void	key_hook(mlx_key_data_t keydata, void *param);
void	close_hook(void *param);

// UTILS
//math_utils.c
void	print_vec3(t_vec3 v);
void	print_camera(t_camera cam);

//FAKE LIST
void		fake_obj_list(t_rt *rt);
void		print_list(t_object *list);
void		add_obj(t_object **list, t_object *new);
t_object	*create_new_obj(t_objtype type, void *data);




#endif