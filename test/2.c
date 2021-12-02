#include "rtweekend.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <mlx.h>

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*data;
	int			bpp;
	int			size_l;
	int			endian;
	int			color[3];
}				t_mlx;

static void	write_color(t_mlx *mlx, t_color pixel_color, int j, int i)
{

	mlx->color[0] = (int)(255.999 * pixel_color.x) << 16;
	mlx->color[1] = (int)(255.999 * pixel_color.y) << 8;
	mlx->color[2] = (int)(255.999 * pixel_color.z);

	int color = mlx->color[0] + mlx->color[1] + mlx->color[2];
	mlx->data[j * 256 + i] = mlx_get_color_value(mlx->mlx_ptr, color);
}

int	main()
{
	t_mlx		mlx;

	const int	image_width = 256;
	const int	image_height = 256;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 700, 400, "rainbow");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, image_width, image_height);
	mlx.data = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.size_l, &mlx.endian);


	printf("P3\n%d %d\n255\n", image_width, image_height);

	int j = 0;
	while (j < image_height)
	{
		fprintf(stderr, "\rScanlines remaining: %d\n", j);
		fflush(stdout);
		int i = 0;
		while (i < image_width)
		{
			t_color pixel_color = {(double)i/(image_width - 1),
								(double)(image_height - 1 - j)/(image_height - 1),
								0.25};
			write_color(&mlx, pixel_color, j, i);
			++i;
		}
		j++;
	}
	fprintf(stderr, "\nDone\n");
	mlx_put_image_to_window ( mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0 );
	mlx_loop(mlx.mlx_ptr);
}