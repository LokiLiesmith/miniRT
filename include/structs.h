#ifndef STRUCTS_H
#define STRUCTS_H

# include "MLX42/MLX42.h"

# define WIDTH 800
# define HEIGHT 800
# define MAX_THREADS 32
# define MAX_DISTANCE 200

# include <pthread.h>
# include <stdatomic.h>

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
	double	light_radius;
}	t_light;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_object		*objects; // linked list of all the objects
	t_object		*selected;
	//RUBBER-BURNING SPEED?
	t_object		**object_arr;
	int				obj_count;
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

typedef enum e_rot_dir
{
	X_CW,
	X_CCW,
	Y_CW,
	Y_CCW,
	Z_CW,
	Z_CCW,
}	t_rot_dir;

typedef enum e_mode
{
	MODE_NONE,
	MODE_ROTATE,
	MODE_SCALE,
	MODE_MOVE
}	t_mode;

typedef enum e_scale
{
	SCALE_RADIUS,
	SCALE_HEIGHT
}	t_scale;

typedef enum e_cap
{
	TOP_CAP,
	BOT_CAP
}	t_cap;

typedef struct s_rt
{
	t_scene			scene;
	mlx_t			*mlx;
	mlx_image_t		*img;
	unsigned int	samples;
	unsigned int	prev_samples;
	t_view			view;
	//MULTITHREADING TINGS
	int				thread_nr;
	pthread_t		threads[MAX_THREADS];
	pthread_mutex_t	px_lock;
	int				px_current;
	int				px_total;
	atomic_int		a_px_current;
	bool			multi_thread;
	bool			pan_drag;
	bool			rotate_drag;
	t_mode			mode;
	t_scale			scale;
	int32_t			prev_mouse_x;
	int32_t			prev_mouse_y;
	//RESIZING
	int32_t			height;
	int32_t			width;
	bool			resize_pending;
	double			last_resize;
	int				view_distance;
	// t_gc	gc;			//gc-list? TODO import from minishell

}	t_rt;

typedef struct s_mouse_data
{
	int32_t	mx;
	int32_t	my;
	int32_t	dx;
	int32_t	dy;
}	t_mouse_data;

typedef enum e_drag_type
{
	PAN_DRAG,
	ROTATE_DRAG
}	t_drag_type;


#endif