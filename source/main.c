#include "miniRT.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->size_l + x * (mlx->bpp / 8));
	*((unsigned int *)dst) = color;
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_scene scene;
	t_camera *camera;
	t_mlx	*mlx;

	init(&scene);
	camera = &scene.camera;
	mlx = &scene.mlx;
	
	for (int y = 0; y < camera->image_height; ++y)
	{
		for (int x = 0; x < camera->image_width; ++x)
		{
			double r = (double)x / (camera->image_width - 1);
			double g = (double)y / (camera->image_height - 1);
			double b = 0.25;

			int ir = (int)(255.999 * r);
			int ig = (int)(255.999 * g);
			int ib = (int)(255.999 * b);

			int color = ir  << 16 | ig << 8 | ib;
			//mlx->addr[(y * camera->image_width) + x] = mlx_get_color_value(mlx->mlx_ptr, color);
			my_mlx_pixel_put(mlx, x, y, color);
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
}