#include "color.h"

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
	
	for (int y = camera->image_width - 1; y >= 0; --y)
	{
		for (int x = 0; x < camera->image_width; ++x)
		{
			write_color(&scene, y, x);
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
}