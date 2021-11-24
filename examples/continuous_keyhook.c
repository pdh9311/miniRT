#include "mlx.h"
#include <stdio.h>

#define KEY_PRESS	2
#define KEY_RELEASE	3

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

int	key_hook(int keycode, t_vars *vars)
{
	printf("key: %d\n", keycode);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "TEST");
	mlx_hook(vars.win, KEY_PRESS, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win, KEY_RELEASE, 1L << 1, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
