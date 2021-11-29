#include "rtweekend.h"
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

int	main()
{
	t_mlx		mlx;

	const int	image_width = 400;
	const int	image_height = 400;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 700, 400, "rainbow");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, image_width, image_height);
	mlx.data = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.size_l, &mlx.endian);

	int j = 0;
	while (j < image_height)
	{
		int i = 0;
		while (i < image_width)
		{
			float r = (double)i / (image_width - 1);
			float g = (image_height - (double)j - 1) / (image_height - 1);
			float b = 0.25;

			int	ir = 255.999 * r;
			int	ig = 255.999 * g;
			int	ib = 255.999 * b;

			mlx.color[0] = ir * 256 * 256;
			mlx.color[1] = ig * 256;
			mlx.color[2] = ib;

			int color = mlx.color[0] + mlx.color[1] + mlx.color[2];
			mlx.data[j * 400 + i] = mlx_get_color_value(mlx.mlx_ptr, color);
			++i;
		}
		j++;
	}
	mlx_put_image_to_window ( mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0 );
	//mlx_loop(mlx.mlx_ptr);
}