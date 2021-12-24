#include "keyhook.h"

void	light_change(t_scene *scene, int keycode)
{
	if (keycode == ENG_L)
		next_light(scene);
	else if (keycode == ENG_K)
		previous_light(scene);
}
