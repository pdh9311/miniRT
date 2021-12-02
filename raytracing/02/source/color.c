#include "color.h"

void	input_color(t_data *data, t_color pixel_color)
{
		data->rgb[0] = 255. * pixel_color.x;
		data->rgb[1] = 255. * pixel_color.y;
		data->rgb[2] = 255. * pixel_color.z;
		data->color = data->rgb[0] << 16 | data->rgb[1] << 8 | data->rgb[2];
}

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
/*
void	write_color(t_mlx *mlx, t_color pixel_color, int j, int i, int samples_per_pixel)
{
	// (void)samples_per_pixel;
	// mlx->color[0] = (int)(255.999 * pixel_color.x) << 16;
	// mlx->color[1] = (int)(255.999 * pixel_color.y) << 8;
	// mlx->color[2] = (int)(255.999 * pixel_color.z);

	// int color = mlx->color[0] + mlx->color[1] + mlx->color[2];
	// my_mlx_pixel_put(mlx, i, j, color);

	double r = pixel_color.x;
	double g = pixel_color.y;
	double b = pixel_color.z;

	double scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;

	mlx->color[0] = (int)(255.999 * clamp(r, 0.0, 0.999)) << 16;
	mlx->color[1] = (int)(255.999 * clamp(g, 0.0, 0.999)) << 8;
	mlx->color[2] = (int)(255.999 * clamp(b, 0.0, 0.999));

	int color = mlx->color[0] + mlx->color[1] + mlx->color[2];
	my_mlx_pixel_put(mlx, i, j, color);
}
*/
