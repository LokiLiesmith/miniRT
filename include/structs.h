#ifndef STRUCTS_H
#define STRUCTS_H

# include "MLX42/MLX42.h"

# define WIDTH 800
# define HEIGHT 800




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

typedef struct s_hit
{
	double	t;//distance from ray origin
	t_vec3	point;//hit point vector
	t_vec3	normal;//normal at hitpoint
	//t_color color??
}	t_hit;





///////////////////////////////////////////////////////////////////////////////
//								OBJECTS										//

typedef enum e_objtype
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_objtype;


typedef struct s_sphere
{
	t_vec3	s;
	int		r;
}	t_sphere;

// typedef struct s_plane;
// typedef struct s_cylinder;

typedef struct s_object
{
	t_objtype		type;
	void			*data;//points to the structs above
	struct s_object	*next;
}	t_object;






///////////////////////////////////////////////////////////////////////////////
//								SCENE									//


//TODO define each element they give us according to pdf

typedef struct s_ambient
{

}	t_ambient;

typedef struct s_camera
{
	double	fov;//in degrees 70.00
	t_vec3	pos;
	t_vec3	dir;
}	t_camera;

typedef struct s_light
{

}	t_light;


typedef struct s_scene
{
	t_ambient	ambient;//A
	t_camera	camera;//C
	t_light		light;//L
	t_object	*objects;//linked list of objects, enum for different handling?
}	t_scene;






///////////////////////////////////////////////////////////////////////////////
//								MAIN STRUCT									//

typedef struct s_rt
{
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*img;
	// t_gc	gc;			//gc-list? TODO import from minishell

}	t_rt;


#endif