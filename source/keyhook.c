#include "keyhook.h"
#include "utils.h"

/*
	[ ADD in Linux or Ubuntu ]
	mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	mlx_destroy_image(scene->mlx.mlx_ptr, scene->mlx.img_ptr);
	mlx_destroy_display(scene->mlx.mlx_ptr);
	free(scene->mlx.mlx_ptr);
	system("leaks miniRT");	// memory leaks check in Mac
*/
int	close_screen(void *param)
{
	t_hlist	*list;
	t_hlist	*tmp;
	t_scene	*scene;

	scene = param;
	list = scene->list;
	while (list != NULL)
	{
		tmp = list->next;
		free(list->object.figure);
		free(list);
		list = tmp;
	}
	free_cameras(scene->cam_list);
	mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	// system("leaks miniRT");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	up_down_rotate(t_camera *cam, int up_down)
{
	t_vec3	r1;
	t_vec3	r2;

	cam->alpha = cam->rotate * up_down;
	r1 = multiply(cam->vector, cos(deg_to_rad(cam->alpha)));
	r2 = multiply(cam->v, sin(deg_to_rad(cam->alpha) * length(cam->vector)));
	cam->vector = add(r1, r2);
	cam->focal = add(cam->origin, \
				multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
	cam->w = unit_vector(subtract(cam->origin, cam->focal));
	cam->v = cross(cam->w, cam->u);
	cam->horizontal = multiply(cam->u, cam->vp_width);
	cam->vertical = multiply(cam->v, cam->vp_height);
}

void	right_left_rotate(t_camera *cam, int right_left)
{
	t_vec3	r1;
	t_vec3	r2;

	cam->beta = cam->rotate * right_left;
	r1 = multiply(cam->vector, cos(deg_to_rad(cam->beta)));
	r2 = multiply(cam->u, sin(deg_to_rad(cam->beta) * length(cam->vector)));
	cam->vector = add(r1, r2);
	cam->focal = add(cam->origin, \
				multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
	cam->w = unit_vector(subtract(cam->origin, cam->focal));
	cam->u = unit_vector(cross(cam->vup, cam->w));
	cam->horizontal = multiply(cam->u, cam->vp_width);
	cam->vertical = multiply(cam->v, cam->vp_height);
}

void	clockwise_rotate(t_camera *cam)
{
	cam->gamma = cam->z_rotate;
	cam->u = add(\
		multiply(cam->u, fabs(cos(deg_to_rad(cam->gamma))) * length(cam->u)), \
		multiply(cam->v, fabs(sin(deg_to_rad(cam->gamma))) * length(cam->u)));
	cam->v = cross(cam->w, cam->u);
	cam->horizontal = multiply(cam->u, cam->vp_width);
	cam->vertical = multiply(cam->v, cam->vp_height);
}

void	counterclockwise_rotate(t_camera *cam)
{
	cam->gamma = -cam->z_rotate;
	cam->u = add(\
		multiply(cam->u, fabs(cos(deg_to_rad(cam->gamma))) * length(cam->u)), \
		multiply(negate(cam->v), \
				fabs(sin(deg_to_rad(cam->gamma))) * length(cam->u)));
	cam->v = cross(cam->w, cam->u);
	cam->horizontal = multiply(cam->u, cam->vp_width);
	cam->vertical = multiply(cam->v, cam->vp_height);
}

void	camera_move(t_camera *cam, int keycode)
{
	if (keycode == ENG_D)
		cam->origin = add(cam->origin, multiply(cam->u, cam->move));
	else if (keycode == ENG_A)
		cam->origin = add(cam->origin, multiply(cam->u, -cam->move));
	else if (keycode == ENG_W)
		cam->origin = add(cam->origin, multiply(cam->v, cam->move));
	else if (keycode == ENG_S)
		cam->origin = add(cam->origin, multiply(cam->v, -cam->move));
	else if (keycode == ENG_E)
		cam->origin = add(cam->origin, \
						multiply(unit_vector(cam->vector), -cam->move));
	else if (keycode == ENG_Q)
		cam->origin = add(cam->origin, \
						multiply(unit_vector(cam->vector), cam->move));
}

void	camera_rotate(t_camera *cam, int keycode)
{
	if (keycode == UP)
		up_down_rotate(cam, 1);
	else if (keycode == DOWN)
		up_down_rotate(cam, -1);
	else if (keycode == RIGHT)
		right_left_rotate(cam, 1);
	else if (keycode == LEFT)
		right_left_rotate(cam, -1);
	else if (keycode == PAGEUP)
		clockwise_rotate(cam);
	else if (keycode == PAGEDOWN)
		counterclockwise_rotate(cam);
}

void	camera_change(t_scene *scene, int keycode)
{
	if (keycode == ENG_N)
		next_camera(scene);
	else if (keycode == ENG_B)
		previous_camera(scene);
}

void	light_change(t_scene *scene, int keycode)
{
	if (keycode == ENG_L)
		next_light(scene);
	else if (keycode == ENG_K)
		previous_light(scene);
}

int	key_hook(int keycode, t_scene *scene)
{
	t_camera	*cam;

	cam = scene->camera;
	if (keycode == ESC)
		close_screen(scene);
	if (keycode == ENG_D || keycode == ENG_A || keycode == ENG_W \
		|| keycode == ENG_S || keycode == ENG_E || keycode == ENG_Q)
		camera_move(cam, keycode);
	else if (keycode == UP || keycode == DOWN || keycode == RIGHT \
		|| keycode == LEFT || keycode == PAGEUP || keycode == PAGEDOWN)
		camera_rotate(cam, keycode);
	else if (keycode == ENG_N || keycode == ENG_B)
		camera_change(scene, keycode);
	else if (keycode == ENG_L || keycode == ENG_K)
		light_change(scene, keycode);
	cam->lower_left_corner = subtract(\
			subtract(subtract(cam->origin, divide(cam->horizontal, 2)), \
			divide(cam->vertical, 2)), cam->w);
	return (0);
}
