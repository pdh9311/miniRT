#include "keyhook.h"

/*
	[ ADD in Linux or Ubuntu ]
	mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	mlx_destroy_image(scene->mlx.mlx_ptr, scene->mlx.img_ptr);
	mlx_destroy_display(scene->mlx.mlx_ptr);
	free(scene->mlx.mlx_ptr);
	system("leaks miniRT");	// memory leaks check in Mac
*/
void close_screen(t_scene *scene)
{
	t_hlist	*list;
	t_hlist	*tmp;

	list = scene->list;
	while (list != NULL)
	{
		tmp = list->next;
		free(list->object.figure);
		free(list);
		list = tmp;
	}
	mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	system("leaks miniRT");
	exit(EXIT_SUCCESS);

}

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == ESC)
		close_screen(scene);
	return (0);
}