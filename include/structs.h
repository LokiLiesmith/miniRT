#ifndef STRUCTS_H
#define STRUCTS_H

# include "MLX42/MLX42.h"

# define WIDTH 800
# define HEIGHT 800
# define MAX_THREADS 32




///////////////////////////////////////////////////////////////////////////////
//								MATH_THINGS									//
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef struct s_object	t_object;

typedef struct s_hit
{
	double		t;//distance from ray origin
	t_vec3		point;//hit point vector
	t_vec3		normal;//normal at hitpoint
	t_color		color;
	t_object	*object;
}	t_hit;

typedef struct s_view
{
	t_vec3	world_up;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
}	t_view;


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
	t_vec3		s;
	double		d;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		axis;
	double		dia;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_object
{
	t_objtype		type;
	void			*data; // points to the structs above
	struct s_object	*next;
}	t_object;

///////////////////////////////////////////////////////////////////////////////
//								SCENE									//

typedef struct s_ambient
{
	double			brightness;
	t_color			color;
}					t_ambient;

typedef struct s_camera
{
	double	fov;//in degrees 70.00
	t_vec3	pos;
	t_vec3	dir;
}	t_camera;

typedef struct s_light
{
	t_vec3	pos;
	double	brightness;
	t_color	color;
}	t_light;


typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_object		*objects; // linked list of all the objects
	t_object		*selected;
}					t_scene;

///////////////////////////////////////////////////////////////////////////////
//								PARSING									//

typedef struct s_found_elements
{
	int	ambient;
	int	camera;
	int	light;
}		t_found;


///////////////////////////////////////////////////////////////////////////////
//								MULTI-THREADING								//

typedef struct s_thread
{
	pthread_t	*thread;
	int			id;

}	t_thread;
///////////////////////////////////////////////////////////////////////////////
//								MAIN STRUCT									//
typedef enum e_mov_dir
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	FORWARD,
	BACKWARD
}	t_mov_dir;

typedef struct s_rt
{
	t_thread		threads[MAX_THREADS];
	t_scene			scene;
	mlx_t			*mlx;
	mlx_image_t		*img;
	unsigned int	samples;
	unsigned int	cores;
	// t_gc	gc;			//gc-list? TODO import from minishell

}	t_rt;




#endif