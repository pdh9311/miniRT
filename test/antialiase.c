#include "miniRT.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "miniRT.h"

t_color	ray_color(t_ray* r, t_hlist *world)
{
	t_hit_record	rec;
	t_vec3			unit_direction;
	float			t;
	t_color			tmp1;
	t_color			tmp2;

	if (hit(world, r, (t_range){0.001, INFINITY}, &rec))
		return ((multiply(add(rec.normal, (t_color){1.0, 1.0, 1.0}), 0.5)));
	unit_direction = unit_vector(r->direction);
	t = 0.5 * (unit_direction.y + 1.0);
	tmp1 = (t_color){1.0, 1.0, 1.0};
	tmp2 = (t_color){0.5, 0.7, 1.0};
	return (add(multiply(tmp1, (1.0 - t)), multiply(tmp2, t)));
}

int	main()
{
	t_mlx			mlx;
	const float	aspect_ratio = 16.0 / 9.0;
	const int		image_width = 1600;
	const int		image_height = (int)(image_width / aspect_ratio);
	const int		samples_per_pixel = 20;

	// World
	t_hlist			*world;

	// Camera
	//t_camera		cam;

	t_sphere		sphere1 = {(t_point3){0.0, 0.0, -1.0}, 0.5};
	t_sphere		sphere2 = {(t_point3){0.0, -100.5, -1.0}, 100.0};
	t_object		hittable1;
	t_object		hittable2;

	hittable1.geometry = _sphere;
	hittable1.pointer = &sphere1;
	hittable2.geometry = _sphere;
	hittable2.pointer = &sphere2;

	world = NULL;
	push(&world, list_(hittable1));
	push(&world, list_(hittable2));

	float			viewport_height = 2.0;
	float			viewport_width = aspect_ratio * viewport_height;
	float			focal_length = 1.0;

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
				float	u = ((i + random_float()) / (image_width - 1));
				float	v = ((image_height - 1 - j + random_float()) / (image_height - 1));
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
