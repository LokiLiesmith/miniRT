/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:36:17 by mrazem            #+#    #+#             */
/*   Updated: 2025/12/04 23:29:16 by mrazem           ###   ########.fr       */
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
# include <time.h>
# include "../include/libft/libft.h"

// VECTOR MATH
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
t_hit		check_cylinder_side(t_ray ray, t_cylinder *cy);


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
void        st_render(t_rt *rt);
// void        st_render(t_rt *rt, int x, int y);
void		set_pixel(mlx_image_t *img, int x, int y, uint32_t color);

//sphere.c
t_hit		intersect_sphere(t_ray ray, t_sphere *sphere);

t_hit		intersect_plane(t_ray ray, t_plane *plane);

//cylinder.c
t_hit		intersect_cylinder(t_ray ray, t_cylinder *cy);
t_hit		check_caps(t_ray ray, t_cylinder *cy);
// t_hit		check_top_cap(t_ray ray, t_cylinder *cy);
t_hit		check_cap(t_ray ray, t_cylinder *cy, int cap);
void		inside_check(t_hit *hit, t_ray ray);

// t_hit		check_base_cap(t_ray ray, t_cylinder *cy);
double		pick_root(double t0, double t1);



//shadows.c
t_vec3 		random_in_unit_sphere(unsigned int seed);
t_view		rotate_disk_to_world_view(t_vec3 normal);
bool		is_backfacing(t_vec3 normal, t_vec3 point, t_vec3 light_pos);
// void		sample_light(t_shadow_vars *v, t_rt *rt, unsigned int x, unsigned int y);


// MLX
//mlx_hooks.c
void	key_hook(mlx_key_data_t keydata, void *param);
void	close_hook(void *param);

//window_resize.c
void	on_resize(int32_t width, int32_t height, void *param);
void	resize_update(void *param);


//EXPERIMENTAL - OBJECT ROTATION
void		mouse_select(mouse_key_t button, action_t action, modifier_key_t mods, void *param);
void		mouse_drag(mouse_key_t button, action_t action, modifier_key_t mods, void *param);
void		drag_hook(void *param);
void		drag_loop(void *param);
void		mouse_scroll(double xdelta, double ydelta, void *param);
t_vec3		vec_rot_around_axis(t_vec3 v, t_vec3 axis, double angle);
//OBSOLETE?
t_vec3		vec_rotate_x(t_vec3 v, double angle);
t_vec3		vec_rotate_y(t_vec3 v, double angle);
t_vec3		vec_rotate_z(t_vec3 v, double angle);

t_hit		check_mouse_intersect(t_ray ray, t_rt *rt);
uint32_t	highlight_color(t_color color);

// OBJECT MOVEMENT
void	move_selection(mlx_key_data_t keydata, t_rt *rt);

void	move_object(t_rt *rt, t_object *selected, double speed, t_mov_dir dir);
void	move_sphere(t_rt *rt, t_sphere *sph, double speed, t_mov_dir dir);
void	move_cylinder(t_rt *rt, t_cylinder *cy, double speed, t_mov_dir dir);
void	move_plane(t_rt *rt, t_plane *pl, double speed, t_mov_dir dir);
// OBJECT ROTATION
void	rotate_selection(mlx_key_data_t keydata, t_rt *rt);
void	rotate_object(t_rt *rt, t_object *selected, t_rot_dir rot_dir);
void	rotate_plane(t_rt *rt, t_plane * pl, t_rot_dir rot_dir, double angle);
void	rotate_cylinder(t_rt *rt, t_cylinder *cy, t_rot_dir rot_dir, double angle);


// OBJECT SCALING
void scale_selection(mlx_key_data_t keydata, t_rt *rt);
void scale_sphere(mlx_key_data_t keydata, t_sphere *sp, t_scale par);
void scale_cylinder(mlx_key_data_t keydata, t_cylinder *cy, t_scale par);



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

// cleanup.c
void		free_objects(t_object **list);
void		free_object_arr(t_scene *scene);
int			exit_success(t_rt *rt);
int			exit_error(t_rt *rt, char *msg);
void		free_all(t_rt *rt);

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
void		print_save_objects(t_rt *rt);

//EXPERIMENTAL - MULTI-THREADING
void	join_threads(t_rt *rt);
void	init_threads(t_rt *rt);
int		get_thread_count(void);
void	*routine(void *arg);
void	render_pixel(t_rt *rt, int px);

uint32_t	set_color(t_rt *rt, t_hit hit, int x, int y);
void		render(t_rt *rt);
void 		mt_render(t_rt *rt);
double		get_time_ms(void);

//RUBBER-BURNING SPEED?
void	build_object_arr(t_scene *scene);
void	free_object_arr(t_scene *scene);
t_hit	check_intersections_arr(t_ray ray, t_rt *rt);
void	render_pixel_arr(t_rt *rt, int px);

//FAKE LIST
void		fake_parsing(t_rt *rt);
void		fake_obj_list(t_rt *rt);
void		print_list(t_object *list);
void		add_obj(t_object **list, t_object *new);
t_object	*create_new_obj(t_objtype type, void *data);

#endif