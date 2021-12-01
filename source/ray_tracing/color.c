#include "color.h"

void	write_color(t_mlx *mlx, t_color pixel_color, int idx, int samples_per_pixel)
{
	int		color;
	double	r;
	double	g;
	double	b;
	double	scale;

	scale = 1.0 / samples_per_pixel;
	r = pixel_color.x * scale;
	g = pixel_color.y * scale;
	b = pixel_color.z * scale;

	mlx->color[0] = (int)(255.999 * clamp(r, 0.0, 0.999)) << 16;
	mlx->color[1] = (int)(255.999 * clamp(g, 0.0, 0.999)) << 8;
	mlx->color[2] = (int)(255.999 * clamp(b, 0.0, 0.999));

	color = mlx->color[0] + mlx->color[1] + mlx->color[2];
	mlx->data[idx] = mlx_get_color_value(mlx->mlx_ptr, color);
}
