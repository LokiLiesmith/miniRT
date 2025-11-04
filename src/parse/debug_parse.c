#include "mini_rt.h"

// Print a vector/point
static void	print_vec3(const char *name, t_vec3 v)
{
	printf("%s: (%.1f, %.1f, %.1f)\n", name, v.x, v.y, v.z);
}

// Print color in hex and RGB
static void	print_color(const char *name, t_color color)
{
	printf("%s: (R:%d, G:%d, B:%d)\n", name, color.r, color.g, color.b);
}

// Print ambient light
static void	print_ambient(t_ambient *ambient)
{
	printf("\n=== AMBIENT LIGHT ===\n");
	printf("Ratio: %.1f\n", ambient->brightness);
	print_color("Color", ambient->color);
}

// Print camera
static void	print_camera(t_camera *camera)
{
	printf("\n=== CAMERA ===\n");
	print_vec3("Position", camera->pos);
	print_vec3("Orientation", camera->vec);
	printf("FOV: %.1f\n", camera->fov);
}

// Print light
static void	print_light(t_light *light)
{
	printf("\n=== LIGHT ===\n");
	print_vec3("Position", light->pos);
	printf("Brightness: %.1f\n", light->brightness);
}

// Print a single object
static void	print_object(t_object *obj, int index)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	printf("\n=== OBJECT #%d ===\n", index);
	printf("Type: ");
	if (obj->type == SPHERE)
	{
		printf("SPHERE\n");
		sp = (t_sphere *)obj->data;
		print_vec3("Center", sp->center);
		printf("Diameter: %.1f\n", sp->dia);
		print_color("Color", sp->color);
	}
	else if (obj->type == PLANE)
	{
		printf("PLANE\n");
		pl = (t_plane *)obj->data;
		print_vec3("Point", pl->point);
		print_vec3("Normal", pl->normal);
		print_color("Color", pl->color);
	}
	else if (obj->type == CYLINDER)
	{
		printf("CYLINDER\n");
		cy = (t_cylinder *)obj->data;
		print_vec3("Center", cy->center);
		print_vec3("Axis", cy->axis);
		printf("Diameter: %.1f\n", cy->dia);
		printf("Height: %.1f\n", cy->height);
		print_color("Color", cy->color);
	}
	else
	{
		printf("UNKNOWN\n");
	}
}

// Print all objects in the linked list
static void	print_objects(t_object *objects)
{
	t_object	*current;
	int			count;

	current = objects;
	count = 0;
	printf("\n======= OBJECTS =======\n");
	if (!current)
	{
		printf("No objects found.\n");
		return ;
	}
	while (current)
	{
		print_object(current, count);
		current = current->next;
		count++;
	}
	printf("\nTotal objects: %d\n", count);
}

// Print the entire scene
void	print_scene(t_scene *scene)
{
	printf("\n");
	printf("╔════════════════════════════════════════╗\n");
	printf("║        SCENE PARSING RESULTS           ║\n");
	printf("╚════════════════════════════════════════╝\n");
	print_ambient(&scene->ambient);
	print_camera(&scene->camera);
	print_light(&scene->light);
	print_objects(scene->objects);
	printf("\n");
	printf("╔════════════════════════════════════════╗\n");
	printf("║           END OF SCENE                 ║\n");
	printf("╚════════════════════════════════════════╝\n");
	printf("\n");
}
