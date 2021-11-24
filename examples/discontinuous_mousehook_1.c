#include "mlx.h"
#include <stdio.h>

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
	mlx_mouse_hook(vars.win, mouse_hook, &vars);	// 입력받은 마우스 값 알아보기
	mlx_loop(vars.mlx);
	return (0);
}
