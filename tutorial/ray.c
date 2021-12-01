#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

#define KEY_PRESS 2
#define KEY_RELEASE 3
#define ESC 53

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;

	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	int		trgb;
}	t_data;

void close(int keycode, t_data *data)	// 이벤트 발생시 call될 함수
{
	mlx_destroy_window(data->mlx, data->win);	// 창을 닫는다.
	/** [ ADD in Linux or Ubuntu ]
	 * mlx_destroy_image(data->mlx, data->img);
	 * mlx_destroy_display(data->mlx);
	 * free(data->mlx);
	 */
	system("leaks ray");	// memory leaks check
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC)
		close(keycode, data);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*((unsigned int *)dst) = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	main(void)
{
	t_data	data;

	data.width = 256 * 2;
	data.height = 256 * 2;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.height, "Tutorial");
	data.img = mlx_new_image(data.mlx, data.width, data.height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	mlx_hook(data.win, KEY_PRESS, 1L<<0, key_hook, &data);
	mlx_hook(data.win, KEY_RELEASE, 1L<<1, key_hook, &data);
	//////////////////////////////////////////////////////////////////
	int i, j;
	for (j = 0; j < data.height ; j++)
	{
		for (i = 0; i < data.width; i++) {
			double r = (double)i / (data.width - 1);	// 0 ≤ r ≤ 1
			double g = (double)(data.height - 1 - j) / (data.height - 1);	// 0 ≤ g ≤ 1
			double b = 0.5;

			int ir = 255.999 * r;
			int ig = 255.999 * g;
			int ib = 255.999 * b;
			data.trgb = create_trgb(0, ir, ig, ib);

			my_mlx_pixel_put(&data, i, j, data.trgb);
		}
	}
	////////////////////////////////////////////////////////////////
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}

