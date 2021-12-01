#include "color.h"

void	write_color(t_mlx *mlx, t_color pixel_color, int idx)
{
	mlx->color[0] = (int)(255.999 * pixel_color.x) << 16;
	mlx->color[1] = (int)(255.999 * pixel_color.y) << 8;
	mlx->color[2] = (int)(255.999 * pixel_color.z);

	int color = mlx->color[0] + mlx->color[1] + mlx->color[2];
	mlx->data[idx] = mlx_get_color_value(mlx->mlx_ptr, color);
}