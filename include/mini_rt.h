/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:36:17 by mrazem            #+#    #+#             */
/*   Updated: 2025/11/16 21:49:03 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "get_next_line.h"
# include "libft/libft.h"
# include "../include/structs.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdatomic.h>
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

//check_intersections.c
t_view		camera_orientation(t_rt *rt);
t_ray		generate_ray(t_rt *rt, int x, int y, t_view view);
t_hit		check_intersections(t_ray ray, t_rt *rt);

//colors.c
uint32_t	rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
t_color		int_to_color(uint32_t color);
uint32_t	normal_to_color(t_vec3 normal);
// uint32_t	calculate_color(t_scene scene, t_hit hit, t_camera camera, t_light light);
uint32_t	calculate_color(t_rt *rt, t_hit hit, unsigned int x, unsigned int y);
double		calc_soft_shadow(t_rt *rt, t_hit hit, unsigned int x, unsigned int y);

// uint32_t	calculate_shadow(t_scene scene, t_hit shadow_hit);
uint32_t	color_scale(t_color color, double factor);

//render.c
void        render(t_rt *rt);
void		set_pixel(mlx_image_t *img, int x, int y, uint32_t color);

//sphere.c
t_hit		intersect_sphere(t_ray ray, t_sphere *sphere);

//shadows.c
t_vec3 		random_in_unit_sphere(unsigned int seed);
t_view		rotate_disk_to_world_view(t_vec3 normal);




// MLX
//mlx_hooks.c
void	key_hook(mlx_key_data_t keydata, void *param);
void	close_hook(void *param);

//EXPERIMENTAL - OBJECT ROTATION
void		mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param);
t_hit		check_mouse_intersect(t_ray ray, t_rt *rt);
// void		clear_selection(t_rt *rt);
// int			get_selected_pos(t_scene *scene);
uint32_t	highlight_color(t_color color);

// OBJECT MOVEMENT
void	move_object(t_rt *rt, t_object *selected, double speed, t_mov_dir dir);
void	move_sphere(t_rt *rt, t_sphere *sph, double speed, t_mov_dir dir);
void	move_cylinder(t_rt *rt, t_cylinder *cy, double speed, t_mov_dir dir);
void	move_plane(t_rt *rt, t_plane *pl, double speed, t_mov_dir dir);

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

/// PRINTS
void		print_ambient(t_ambient *ambient);
void		print_color(const char *name, t_color color);
void		print_scene(t_scene *scene);
void		print_camera(t_camera *camera);
void		print_light(t_light *light);
void		print_object(t_object *obj, int index);
void		print_vec3(const char *name, t_vec3 v);
void		print_objects(t_object *objects);

void		print_save_scene(t_rt *rt);
void		print_save_object(t_object *obj);
void		print_save_objects(t_object *objects);

//EXPERIMENTAL - MULTI-THREADING
void	join_threads(t_rt *rt);
void	init_threads(t_rt *rt);
int		get_thread_count(void);
void	*routine(void *arg);
void	render_pixel(t_rt *rt, int px);

//FAKE LIST
void		fake_parsing(t_rt *rt);
void		fake_obj_list(t_rt *rt);
void		print_list(t_object *list);
void		add_obj(t_object **list, t_object *new);
t_object	*create_new_obj(t_objtype type, void *data);



#endif