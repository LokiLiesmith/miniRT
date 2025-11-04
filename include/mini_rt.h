/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:36:17 by mrazem            #+#    #+#             */
/*   Updated: 2025/11/04 13:54:56 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "get_next_line.h"
# include "libft/libft.h"
# include "structs.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
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
///////////////////////////////////////////////////////////////////////////////
//								PARSING										//

// file_check.c
int			check_type_identifier(char *line, t_found *found);
int			check_line_format(char *line, int valid);
int			check_acl(t_found *found, int found_valid_line);
int			parse_scene_file(const char *file, t_scene *scene, int val,
				t_found *found);
int			check_input(int ac, char **av, t_scene *scene);

// acl_parse.c
int			parse_ambient(char **strs, t_ambient *ambient);
int			parse_camera(char **strs, t_camera *camera, int i);
int			parse_light(char **strs, t_light *light);
int			parse_elements(char *line, t_scene *scene);

// ft_atod.c
double		ft_atod(char *str);
long		ft_atol(char *str);

// objs_parse.c
int			parse_sp(char **strs, t_object **objects);
int			parse_pl_normal(int i, t_plane *pl, double xyz[3]);
int			parse_pl(char **strs, t_object **objects, int i);
int			parse_cy_cont(int i, double xyz[3], char **strs, t_cylinder *cy);
int			parse_cy(char **strs, t_object **objects, int i);

// parse_utils
int			is_valid_double(char *str, int has_dot);
void		free_split(char **split_strs);
int			count_split(char **split_strs);
int			is_line_empty_or_whitespace(const char *line);
void		strip_newline(char *line);

// parse_xyz_rgb.c
int			check_if_int(char *str);
int			parse_xyz(char *s, double xyz[3]);
int			parse_rgb(char *rgb_str, t_color *color, int i);

// linked_list_utils.c
t_object	*create_new_obj(t_objtype type, void *data);
void		add_obj(t_object **list, t_object *new);

// only for debugging parsing - delete after pls
void		print_scene(t_scene *scene);

///////////////////////////////////////////////////////////////////////////////
//								UTILS										//
void		free_objects(t_object **list);

#endif