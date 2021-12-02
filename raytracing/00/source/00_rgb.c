#include <stdio.h>
#include "keyhook.h"

int	main(void)
{
	t_data	data;

	int		win_width = 256 * 2;
	int		win_height = 256 * 2;
	int		img_width = win_width;
	int		img_height = win_height;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, win_width, win_height, "Tutorial");
	data.img = mlx_new_image(data.mlx, img_width, img_height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	mlx_hook(data.win, KEY_PRESS, 1L<<0, key_hook, &data);
	//////////////////////////////////////////////////////////////////
	int i, j;
	for (j = img_height - 1; j >= 0 ; j--) {
		fprintf(stderr, "Scanlines remaining: %d\n", j);	fflush(stderr);
		for (i = 0; i < img_width; i++) {
			double r = (double)i / (img_width - 1);	// 0 ≤ r ≤ 1
			double g = (double)j / (img_height - 1);	// 0 ≤ g ≤ 1
			double b = 0.3;

			// high dynamic range
			data.rgb[0] = 255. * r;
			data.rgb[1] = 255. * g;
			data.rgb[2] = 255. * b;
			data.color = data.rgb[0] << 16 | data.rgb[1] << 8 | data.rgb[2];

			my_mlx_pixel_put(&data, i, j, data.color);
		}
	}
	fprintf(stderr, "\nDone.\n");	fflush(stderr);
	////////////////////////////////////////////////////////////////
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
