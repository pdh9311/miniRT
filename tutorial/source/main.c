#include "mlx.h"
#include "libft.h"
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

	data.width = 1980;
	data.height = 1080;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.height, "Tutorial");
	data.img = mlx_new_image(data.mlx, data.width, data.height);
	//////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
