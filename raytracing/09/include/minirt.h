#ifndef MINIRT_H
# define MINIRT_H

#include "mlx.h"

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	int		rgb[3];
	int		color;
}	t_data;

typedef int	t_bool;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
