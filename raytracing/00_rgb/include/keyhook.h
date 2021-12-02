#ifndef KEYHOOK_H
# define KEYHOOK_H

# define KEY_PRESS		2
# define KEY_RELEASE	3

# include "minirt.h"
# include "keycode.h"
# include <stdlib.h>

void	close(t_data *data);
int		key_hook(int keycode, t_data *data);

#endif
