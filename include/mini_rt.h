#ifndef MINI_RT_H
#define MINI_RT_H

#include "structs.h"
# include <stdio.h>
# include "libft/libft.h"
#include <fcntl.h>
#include "get_next_line/get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

///////////////////////////////////////////////////////////////////////////////
//								PARSING										//

// file_check.c
int	is_line_empty_or_whitespace(const char *line);
int	check_type_identifier(char *line, t_found_elements *found);
int	check_line_format(char *line);
void strip_newline(char *line);
int	parse_scene_file(const char *filename, t_scene *scene);
int	check_input(int ac, char **av, t_scene *scene);

// acl_parse.c
int	parse_ambient(char **strs, t_ambient *ambient);
int	parse_camera(char **strs, t_camera *camera);
int	parse_light(char **strs, t_light *light);
int	parse_elements(char *line, t_scene *scene);

// ft_atod.c
double	ft_atod(char *str);
long	ft_atol(char *str);

// objs_parse.c
int	parse_sp(char **strs, t_object **objects);
int	parse_pl(char **strs, t_object **objects, int i);
int	parse_cy(char **strs, t_object **objects, int i);

// parse_utils
int	is_valid_double(char *str, int has_dot);
void	free_split(char **split_strs);
int	count_split(char **split_strs);
int parse_xyz(char *s, double xyz[3]);
int	check_if_int(char *str);
int	parse_rgb(char *rgb_str, t_color *color, int i);

// linked_list_utils.c
t_object	*create_new_obj(t_objtype type, void *data);
void	add_obj(t_object **list, t_object *new);

// just for debugging - delete pls
void print_scene(t_scene *scene);

///////////////////////////////////////////////////////////////////////////////
//								UTILS										//
void free_objects(t_object **list);

#endif