#include "mlx.h"
#include "keycode.h"
#include <stdlib.h>
#include <stdio.h>

#define KEY_PRESS 2
#define KEY_RELEASE 3
#define BTN_PRESS 4
#define BTN_RELEASE 5

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

void close(int keycode, t_vars *vars)	// 이벤트 발생시 call될 함수
{
	mlx_destroy_window(vars->mlx, vars->win);	// 창을 닫는다.
	/** [ ADD in Linux or Ubuntu ]
	 * mlx_destroy_image(vars->mlx, vars->img);
	 * mlx_destroy_display(vars->mlx);
	 * free(vars->mlx);
	 */
	system("leaks closehook");	// memory leaks check
	exit(EXIT_SUCCESS);
}

// ESC 입력 받을 시 종료
int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		close(keycode, vars);
	else
		printf("key: %d\n", keycode);
	return (0);
}

int	mouse_hook(int keycode, t_vars *vars)
{
	printf("mouse: %d\n", keycode);
	return (0);
}

/** Description
 * 키보드, 마우스 입력을 받아서 입력 받은 값을 출력하다가
 * ESC 입력 받을시 창을 닫고 메모리 해제 되었는지 확인하고 종료.
 */
int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "TEST");
	mlx_hook(vars.win, KEY_PRESS, 1L<<0, key_hook, &vars);
	mlx_hook(vars.win, KEY_RELEASE, 1L<<1, key_hook, &vars);
	mlx_hook(vars.win, BTN_PRESS, 1L<<2, mouse_hook, &vars);
	mlx_hook(vars.win, BTN_RELEASE, 1L<<3, mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
