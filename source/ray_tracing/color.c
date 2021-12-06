#include "color.h"

static void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->size_l + x * (mlx->bpp / 8));
	*((unsigned int *)dst) = color;
}

void	write_color(t_scene *scene, int y, int x)
{
	t_camera	*camera;
	int			ir;
	int			ig;
	int			ib;
	int			color;

	camera = &scene->camera;
	double r = (double)x / (camera->image_width - 1);
	double g = (double)(camera->image_height - y - 1) / (camera->image_height - 1);
	double b = 0.25;
	ir = (int)(255.999 * r);
	ig = (int)(255.999 * g);
	ib = (int)(255.999 * b);
	color = ir  << 16 | ig << 8 | ib;
	my_mlx_pixel_put(&scene->mlx, x, y, color);
}
