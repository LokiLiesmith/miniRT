#ifndef STRUCTS_H
# define STRUCTS_H
# include "MLX42/MLX42.h"

# define WIDTH 800
# define HEIGHT 800

typedef struct s_rt
{
	// t_scene	scene;
	mlx_t			*mlx;
	mlx_image_t		*img;
	// t_gc	gc;			//gc-list? TODO import from minishell

}					t_rt;

///////////////////////////////////////////////////////////////////////////////
//								MATH_THINGS									//
typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_ray
{
	// origin point with 3 coords;
	// direction; scalar?;
}					t_ray;

///////////////////////////////////////////////////////////////////////////////
//								OBJECTS										//

typedef enum e_objtype
{
	SPHERE,
	PLANE,
	CYLINDER
}					t_objtype;

typedef struct s_sphere
{
	t_vec3 center;
	double dia;
	t_color color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3 point;
	t_vec3 vec;
	t_color color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3 center;
	t_vec3 vec;
	double dia;
	double height;
	t_color color;
}	t_cylinder;

typedef struct s_object
{
	t_objtype		type;
	void *data; // points to the structs above
	struct s_object	*next;
}					t_object;

///////////////////////////////////////////////////////////////////////////////
//								SCENE									//

typedef struct s_ambient
{
	double			brightness;
	t_color			color;
}					t_ambient;

typedef struct s_camera
{
	t_vec3		pos;
	t_vec3		vec;
	double		fov;

}					t_camera;

typedef struct s_light
{
	t_vec3		pos;
	double			brightness;
}					t_light;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_object *objects; // linked list of all the objects
}					t_scene;

///////////////////////////////////////////////////////////////////////////////
//								PARSING									//

typedef struct s_found_elements
{
	int	ambient;
	int	camera;
	int	light;
	int	sp_count;
	int	pl_count;
	int	cy_count;
}		t_found_elements; // after final checks/debugging i think u can remove the object counts(?)

#endif