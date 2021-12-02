#include <stdio.h>
#include "keyhook.h"
#include <stdlib.h>


void close_screen(t_data *data)	// 이벤트 발생시 call될 함수
{
	mlx_destroy_window(data->mlx, data->win);	// 창을 닫는다.
	//  [ ADD in Linux or Ubuntu ]
	// mlx_destroy_image(data->mlx, data->img);
	// mlx_destroy_display(data->mlx);
	// free(data->mlx);

	system("leaks tutorial");	// memory leaks check in Mac
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_screen(data);
	return (0);
}
