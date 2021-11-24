#include "mlx.h"
#include <stdio.h>

#define BTN_PRESS	4
#define BTN_RELEASE	5

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

int mouse_hook(int keycode, t_vars *vars)
{
	printf("mouse: %d\n", keycode);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "TEST");
	mlx_hook(vars.win, BTN_PRESS, 1L << 2, mouse_hook, &vars);
	mlx_hook(vars.win, BTN_RELEASE, 1L << 3, mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
