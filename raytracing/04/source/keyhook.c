#include "keyhook.h"
#include "minirt.h"
#include <stdlib.h>
#include "rtweekend.h"
#include <math.h>
#include <stdio.h>

void close_screen(t_data *data)	// 이벤트 발생시 call될 함수
{
	mlx_destroy_window(data->mlx, data->win);	// 창을 닫는다.
	// [ ADD in Linux or Ubuntu ]
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
	if (keycode == ENG_Q)
		data->origin.x += 0.1;
	if (keycode == ENG_W)
		data->origin.x -= 0.1;
	if (keycode == ENG_A)
		data->origin.y += 0.1;
	if (keycode == ENG_S)
		data->origin.y -= 0.1;
	if (keycode == ENG_Z)
		data->origin.z += 0.1;
	if (keycode == ENG_X)
		data->origin.z -= 0.1;
	if (keycode == NUM_1) {
		data->alpha++;
		data->focal.y = -data->facal_length * sin(degrees_to_radians(data->alpha));
		data->focal.z = -data->facal_length * cos(degrees_to_radians(data->alpha));
		data->lower_left_corner = add(subtract(data->focal, data->origin), add(divide(data->horizontal, -2), divide(data->vertical, -2)));
	}
	if (keycode == NUM_2) {
		data->alpha--;
		data->focal.y = -data->facal_length * sin(degrees_to_radians(data->alpha));
		data->focal.z = -data->facal_length * cos(degrees_to_radians(data->alpha));
		data->lower_left_corner = add(subtract(data->focal, data->origin), add(divide(data->horizontal, -2), divide(data->vertical, -2)));
	}
	if (keycode == NUM_3) {
		data->beta++;
		data->focal.x = -data->facal_length * sin(degrees_to_radians(data->beta));
		data->focal.z = -data->facal_length * cos(degrees_to_radians(data->beta));
		data->lower_left_corner = add(subtract(data->focal, data->origin), add(divide(data->horizontal, -2), divide(data->vertical, -2)));
	}
	if (keycode == NUM_4) {
		data->beta--;
		data->focal.x = -data->facal_length * sin(degrees_to_radians(data->beta));
		data->focal.z = -data->facal_length * cos(degrees_to_radians(data->beta));
		data->lower_left_corner = add(subtract(data->focal, data->origin), add(divide(data->horizontal, -2), divide(data->vertical, -2)));
	}
	fprintf(stderr,"%lf %lf |%lf %lf %lf\n", data->alpha, data->beta, data->origin.x, data->origin.y, data->origin.z);
	fflush(stderr);
	return (0);
}
