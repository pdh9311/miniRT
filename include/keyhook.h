#ifndef KEYHOOK_H
# define KEYHOOK_H

# include "keycode.h"
# include "miniRT.h"

# define KEY_PRESS		2
# define KEY_RELEASE	3
# define BTN_PRESS		4
# define BTN_RELEASE	5
# define MOUSE_MOVE		6
# define DESTROY		17

int		close_screen(void *param);
int		key_hook(int keycode, t_scene *scene);

#endif
