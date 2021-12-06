#include "miniRT.h"

void	init_mlx(t_mlx *arg)
{
	arg->mlx_ptr = mlx_init();
	arg->win_ptr = mlx_new_window(mlx.mlx_ptr, image_width, image_height, "rainbow");
	arg->img_ptr = mlx_new_image(mlx.mlx_ptr, image_width, image_height);
	arg->data = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.size_l, &mlx.endian);
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	t_scene scene;
	init_mlx(&scene.mlx);
}

/*
int	main()
{
	t_mlx			mlx;
	const double	aspect_ratio = 16.0 / 9.0;
	const int		image_width = 1600;
	const int		image_height = (int)(image_width / aspect_ratio);
	const int		samples_per_pixel = 100;

	// World
	t_hlist			*world;

	// Camera
	//t_camera		cam;

	t_sphere		sphere1 = {(t_point3){0.0, 0.0, -1.0}, 0.5};
	t_sphere		sphere2 = {(t_point3){0.0, -100.5, -1.0}, 100.0};
	t_hittable		hittable1;
	t_hittable		hittable2;

	hittable1.geometry = _sphere;
	hittable1.pointer = &sphere1;
	hittable2.geometry = _sphere;
	hittable2.pointer = &sphere2;

	world = NULL;
	push(&world, list_(hittable1));
	push(&world, list_(hittable2));

	double			viewport_height = 2.0;
	double			viewport_width = aspect_ratio * viewport_height;
	double			focal_length = 1.0;

	t_point3			origin = {0, 0, 0};
	t_vec3			horizontal = {viewport_width, 0, 0};
	t_vec3			vertical = {0, viewport_height, 0};
	t_vec3			tmp = {0, 0, focal_length};
	t_vec3			lower_left_corner = subtract(subtract(subtract(origin, divide(horizontal, 2)), \
												divide(vertical, 2)), tmp);

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, image_width, image_height, "rainbow");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, image_width, image_height);
	mlx.data = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.size_l, &mlx.endian);

	printf("P3\n%d %d\n255\n", image_width, image_height);
	int j = 0;
	while (j < image_height)
	{
		fprintf(stderr, "\rScanlines remaining: %d\n", j);
		fflush(stdout);
		int i = 0;
		while (i < image_width)
		{
			t_color	pixel_color = {0.0, 0.0, 0.0};
			for (int s = 0; s < samples_per_pixel; ++s)
			{
				double	u = ((i + random_double()) / (image_width - 1));
				double	v = ((image_height - 1 - j + random_double()) / (image_height - 1));
				t_ray		r;
				r.origin = origin;
				r.direction = subtract(add(add(lower_left_corner, multiply(horizontal, u)), multiply(vertical, v)), origin);
				add_(&pixel_color, ray_color(&r, world));
			}
			write_color(&mlx, pixel_color, (j * image_width + i), samples_per_pixel);
			++i;
		}
		j++;
	}
	fprintf(stderr, "\nDone\n");
	mlx_put_image_to_window ( mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0 );
	mlx_loop(mlx.mlx_ptr);
}
*/