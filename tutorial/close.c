#define ESC 53

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC)
		close(keycode, data);
	return (0);
}
