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
//								OBJECTS										//

typedef enum e_objtype
{
	SPHERE,
	PLANE,
	CYLINDER
}					t_objtype;

// to figure out
// typedef struct s_sphere;
// typedef struct s_plane;
// typedef struct s_cylinder;

typedef struct s_object
{
	t_objtype		type;
	void *data; // points to the structs above
	struct s_object	*next;
}					t_object;

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
//								SCENE									//

typedef struct s_xyz_coord
{
	double			x;
	double			y;
	double			z;
}					t_xyz_coord;
// thought this is better for naming? or should i just use the t_vec3 struct for xyz coordinates too?

typedef struct s_ambient
{
	double			ratio;
	t_color			a_col;
}					t_ambient;

typedef struct s_camera
{
	t_xyz_coord		c_pos;
	t_vec3			c_vec;
	double			fov;

}					t_camera;

typedef struct s_light
{
	t_xyz_coord		l_pos;
	double			brightness;
}					t_light;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_object *objects; // linked list of objects, enum for different handling?
}					t_scene;

#endif