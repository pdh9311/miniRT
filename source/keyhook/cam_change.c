#include "keyhook.h"

void	camera_change(t_scene *scene, int keycode)
{
	if (keycode == ENG_N)
		next_camera(scene);
	else if (keycode == ENG_B)
		previous_camera(scene);
}
