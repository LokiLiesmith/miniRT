#ifndef STRUCTS_H
#define STRUCTS_H
#include "MLX42/MLX42.h"

# define WIDTH 800
# define HEIGHT 800

typedef struct s_rt
{
	// t_scene	scene;			
	mlx_t		*mlx;
	mlx_image_t	*img;
	// t_gc	gc;			//gc-list? TODO import from minishell

}	t_rt;





///////////////////////////////////////////////////////////////////////////////
//								OBJECTS										//

typedef enum e_objtype
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_objtype;

//to figure out
// typedef struct s_sphere;
// typedef struct s_plane;
// typedef struct s_cylinder;

typedef struct s_object
{
	t_objtype		type;
	void			*data;//points to the structs above
	struct s_object	*next;
}	t_object;






///////////////////////////////////////////////////////////////////////////////
//								MATH_THINGS									//
typedef struct s_vec3
{
	double x;
	double y;
	double z;
}	t_vec3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_ray
{
	// origin point with 3 coords;
	// direction; scalar?;
}	t_ray;





///////////////////////////////////////////////////////////////////////////////
//								SCENE									//


//TODO define each element they give us according to pdf

typedef struct s_ambient
{

}	t_ambient;

typedef struct s_camera
{

}	t_camera;

typedef struct s_light
{

}	t_light;


typedef	struct s_scene
{
	t_ambient	ambient;//A
	t_camera	camera;//C
	t_light		light;//L
	t_object	*objects;//linked list of objects, enum for different handling?
}	t_scene;




#endif