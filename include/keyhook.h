#ifndef KEYHOOK_H
# define KEYHOOK_H

# include "keycode.h"
# include "miniRT.h"

# define KEY_PRESS		2
# define KEY_RELEASE	3

void	close_screen(t_scene *scene);
int		key_hook(int keycode, t_scene *scene);

#endif
