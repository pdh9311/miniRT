#include "keyhook.h"

/*
	[ ADD in Linux or Ubuntu ]
	mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	mlx_destroy_image(scene->mlx.mlx_ptr, scene->mlx.img_ptr);
	mlx_destroy_display(scene->mlx.mlx_ptr);
	free(scene->mlx.mlx_ptr);
	system("leaks miniRT");	// memory leaks check in Mac
*/
int close_screen(void *param)
{
	t_hlist	*list;
	t_hlist	*tmp;
	t_scene *scene;

	scene = param;
	list = scene->list;
	while (list != NULL)
	{
		tmp = list->next;
		free(list->object.figure);
		free(list);
		list = tmp;
	}
	mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	// system("leaks miniRT");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	key_hook(int keycode, t_scene *scene)
{
	t_camera	*cam;
	double		x;
	double		y;
	double		z;

	cam = &scene->camera;
	x = scene->camera.origin.x;
	y = scene->camera.origin.y;
	z = scene->camera.origin.z;
	if (keycode == ESC)
		close_screen(scene);
	if (keycode == ENG_D)
		update(&cam->origin, x + 0.1, y, z);
	else if (keycode == ENG_A)
		update(&cam->origin, x - 0.1, y, z);
	else if (keycode == ENG_W)
		update(&cam->origin, x, y + 0.1, z);
	else if (keycode == ENG_S)
		update(&cam->origin, x, y - 0.1, z);
	else if (keycode == ENG_E)
		update(&cam->origin, x, y, z + 0.1);
	else if (keycode == ENG_Q)
		update(&cam->origin, x, y, z - 0.1);
	else if (keycode == BACKTIK)
		update(&cam->origin, cam->origin2.x, cam->origin2.y, cam->origin2.z);
	cam->lower_left_corner = subtract(
		subtract(subtract(cam->origin, divide(cam->horizontal, 2)),
			divide(cam->vertical, 2)), cam->w);
	printf("%lf %lf %lf\n", scene->camera.origin.x, scene->camera.origin.y, scene->camera.origin.z);
	return (0);
}
