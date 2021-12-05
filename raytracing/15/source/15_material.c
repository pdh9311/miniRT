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
	// int is_hit = hit(world, r, 0.001, INFINITY, &rec);
	// if (is_hit) {
	if (hit(world, r, 0.001, INFINITY, &rec)) {
		t_ray	scattered;		// 산발적인
		t_color	attenuation;	// 감쇠
		if (scatter(r, &rec, &attenuation, &scattered))
			return (multiply__(attenuation, ray_color(scattered, world, depth - 1)));
		return (color_(0.0, 0.0, 0.0));

		// t_vec3	target = add(rec.p, random_unit_hemisphere(rec.normal));
		// t_ray	new_ray;
		// new_ray.origin = rec.p;
		// new_ray.direction = subtract(target, rec.p);
		// return (multiply(ray_color(new_ray, world, depth - 1), 0.5));	// 0.5 : 밝기를 0.5 배 낮춘다는 의미로 볼 수 있다.
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
	int		img_height = 450;
	int		img_width = img_height * aspect_ratio;
	int		samples_per_pixel = 10;
	int		depth = 30;

	// World
	t_hlist		*world;

	t_sphere	sphere1 = {point3_(0.0, -100.5, -1.0), 100};
	t_sphere	sphere2 = {point3_(0.0, 0.0, -1.0), 0.5};
	t_sphere	sphere3 = {point3_(-1.0, 0.0, -1.0), 0.5};
	t_sphere	sphere4 = {point3_(1.0, 0.0, -1.0), 0.5};
	t_hittable	hittable1;
	t_hittable	hittable2;
	t_hittable	hittable3;
	t_hittable	hittable4;

	hittable1.geometry = _sphere;
	hittable1.pointer = &sphere1;
	hittable1.material.albedo = color_(0.8, 0.8, 0.0);
	hittable1.material.surface = lambertian;

	hittable2.geometry = _sphere;
	hittable2.pointer = &sphere2;
	hittable2.material.albedo = color_(0.7, 0.3, 0.3);
	hittable2.material.surface = lambertian;

	hittable3.geometry = _sphere;
	hittable3.pointer = &sphere3;
	hittable3.material.albedo = color_(0.8, 0.8, 0.8);
	hittable3.material.surface = metal;

	hittable4.geometry = _sphere;
	hittable4.pointer = &sphere4;
	hittable4.material.albedo = color_(0.8, 0.6, 0.2);
	hittable4.material.surface = metal;

	world = NULL;
	push(&world, list_(hittable1));
	push(&world, list_(hittable2));
	push(&world, list_(hittable3));
	push(&world, list_(hittable4));

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
				r.direction = subtract(add(cam.lower_left_corner, add(multiply(cam.horizontal, u), multiply(cam.vertical, v))), cam.origin);
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
