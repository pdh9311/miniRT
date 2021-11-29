#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

int		value;
void	*mlx;
void	*win;

int	key_hook(int keycode, void *param)
{
	char buf[10];

	if (keycode == 53)
	{
		mlx_destroy_window(mlx, win);
		system("leaks mlx_test");
		exit (EXIT_SUCCESS);
	}
	(void)param;
	sprintf(buf, "%d", value);
	value++;
	if (value > 10000000)
		value = 0;
	mlx_clear_window(mlx, win);
	mlx_string_put(mlx, win, 100, 100, 0xffffff, buf);
	return (0);
}

int	loop_hook(void *param)
{
	(void)param;
	///
	return (0);
}

int	main()
{
	mlx = mlx_init();
	if (mlx == NULL)
	{
		fprintf(stderr, "mlx init failed.\n");
		exit(EXIT_FAILURE);
	}
	win = mlx_new_window(mlx, 300, 300, "New Window");
	mlx_key_hook(win, &key_hook, NULL);
	fprintf(stderr, "hi\n");
	mlx_loop_hook(mlx, &loop_hook, NULL);
	mlx_loop(mlx);
}
