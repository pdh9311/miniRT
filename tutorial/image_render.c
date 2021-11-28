#include "mlx.h"
#include <stdio.h>

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

	int		int_color;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*((unsigned int *)dst) = color;
}

int	main(void)
{
	t_data	data;

	data.width = 256;
	data.height = 256;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.height, "Tutorial 1");
	data.img = mlx_new_image(data.mlx, data.width, data.height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	//////////////////////////////////////////////////////////////////
	int i, j;
	for (j = 0; j < data.height ; j++)
	{
		for (i = 0; i < data.width; i++) {
			double r = (double)i / (data.width - 1);	// 0 ≤ r ≤ 1
			double g = (double)j / (data.height - 1);	// 0 ≤ g ≤ 1
			double b = 0.5;

			int ir = 255.999 * r;
			int ig = 255.999 * g;
			int ib = 255.999 * b;

			// data.int_color = ir * 256 * 256 + ig * 256 + ib;
			data.int_color = ir << 16 | ig << 8 | ib;
			my_mlx_pixel_put(&data, i, j, data.int_color);
		}
	}
	////////////////////////////////////////////////////////////////
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}

