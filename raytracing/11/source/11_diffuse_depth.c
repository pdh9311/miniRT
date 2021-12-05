#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "keyhook.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <math.h>
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

t_color	ray_color(const t_ray r, t_hlist *world, int depth)
{
	t_hit_record	rec;

	if (depth <= 0)
		return (color_(0.0, 0.0, 0.0));
	int is_hit = hit(world, r, 0.001, INFINITY, &rec);
	if (is_hit) {
		t_vec3	target = add(rec.normal, random_in_unit_sphere());
		t_ray	new_ray;
		new_ray.origin = rec.p;
		new_ray.direction = subtract(target, rec.p);
		return (multiply(ray_color(new_ray, world, depth - 1), 0.5));	// 0.5: ray는 물체를 반사할 때마다 절반(0.5)의 에너지를 흡수한다는 의미. (밝기를 0.5 배 낮춘다는 의미로도 볼 수 있다.)
	}
	t_vec3	unit_direction = unit_vector(r.direction);
	double t = 0.5 * (unit_direction.y + 1.0);
	return (add(multiply(vec3_(1.0, 1.0, 1.0), 1.0 - t),
				multiply(vec3_(0.5, 0.7, 1.0), t)));
}

int	main(void)
{
	t_data	data;

	// Image
	double	aspect_ratio = 16.0 / 9.0;
	int		img_height = 900;
	int		img_width = img_height * aspect_ratio;
	int		samples_per_pixel = 20;
	int		depth = 50;

	// World
	t_hlist		*world;

	world = NULL;
	t_sphere	sphere1 = {point3_(0.5, 0.0, -1.0), 0.5};
	t_sphere	sphere2 = {point3_(0.0, -100.5, -1.0), 100};
	t_sphere	sphere3 = {point3_(-0.5, 0.0, -1.0), 0.5};

	t_hittable	hittable1 = {_sphere, &sphere1};
	t_hittable	hittable2 = {_sphere, &sphere2};
	t_hittable	hittable3 = {_sphere, &sphere3};

	push(&world, list_(hittable1));
	push(&world, list_(hittable2));
	push(&world, list_(hittable3));

	// Camera
	double	viewport_height = 2.0;
	double	viewport_width = aspect_ratio * viewport_height;
	int		facal_length = 1.0;

	t_camera	cam;
	cam.origin = point3_(0, 0, 0);
	cam.horizontal = vec3_(viewport_width, 0, 0);
	cam.vertical = vec3_(0, viewport_height, 0);
	t_vec3 focal = vec3_(0, 0, -facal_length);
	cam.lower_left_corner = add(subtract(focal, cam.origin), add(divide(cam.horizontal, -2), divide(cam.vertical, -2)));

	// mlx setting1
	int		win_height = img_height;
	int		win_width = img_width;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, win_width, win_height, "Tutorial");
	data.img = mlx_new_image(data.mlx, img_width, img_height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	mlx_hook(data.win, KEY_PRESS, 1L<<0, key_hook, &data);

	//////////////////////////////////////////////////////////////////

	// Render
	for (int j = img_height - 1; j >= 0 ; j--) {
		fprintf(stderr, "Scanlines remaining: %d\n", j);	fflush(stderr);
		for (int i = 0; i < img_width; i++) {
			t_color pixel_color = color_(0.0, 0.0, 0.0);
			for (int s = 0; s < samples_per_pixel; s++) {
				double u = ((double)i + random_double())/ (img_width - 1);
				double v = (double)(img_height - 1 - j + random_double()) / (img_height - 1);
				t_ray r;
				r.origin = cam.origin;
				r.direction = add(cam.lower_left_corner, add(multiply(cam.horizontal, u), multiply(cam.vertical, v)));
				add_(&pixel_color, ray_color(r, world, depth));
			}
			input_color(&data, pixel_color, samples_per_pixel);
			my_mlx_pixel_put(&data, i, j, data.color);
			// usleep(100000);
		}
	}
	fprintf(stderr, "\nDone.\n");	fflush(stderr);
	////////////////////////////////////////////////////////////////

	// mlx setting2
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
