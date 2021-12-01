#include "color.h"

/*
void write_color(t_color pixel_color, int samples_per_pixel)
{
	double	r;
	double	g;
	double	b;
	double	scale;
	int		ir;
	int		ig;
	int		ib;

	r = pixel_color.x;
	g = pixel_color.y;
	b = pixel_color.z;
	scale = 1.0 / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);
	ir = (int)(256 * clamp(r, 0.0, 0.999));
	ig = (int)(256 * clamp(g, 0.0, 0.999));
	ib = (int)(256 * clamp(b, 0.0, 0.999));
	printf("%d %d %d\n", ir, ig, ib);
}
*/

void	write_color(t_mlx *mlx, t_color pixel_color, int j, int i, int width)
{

	mlx->color[0] = (int)(255.999 * pixel_color.x) << 16;
	mlx->color[1] = (int)(255.999 * pixel_color.y) << 8;
	mlx->color[2] = (int)(255.999 * pixel_color.z);

	int color = mlx->color[0] + mlx->color[1] + mlx->color[2];
	mlx->data[j * width + i] = mlx_get_color_value(mlx->mlx_ptr, color);
}