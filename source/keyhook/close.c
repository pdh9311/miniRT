#include "keyhook.h"

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
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
