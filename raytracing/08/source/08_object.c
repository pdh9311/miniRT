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

///////// ray_color
/*
t_color	ray_color(const t_ray r)
{
	t_point3		center = vec3_(0.0, 0.0, -1.0);
	t_hit_record	rec;
	double			t = hit_sphere(center, 0.5, r, 0, INFINITY, &rec);
	if (t > 0.0) {
		t_vec3	N = rec.normal;			// N : 법선 단위 벡터
		return (multiply(vec3_(N.x + 1, N.y + 1, N.z + 1), 0.5));	// -1 ≤ N ≤ 1 을 0 과 1 사이의 범위로 변환.
	}
	t_vec3	unit_direction = unit_vector(r.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	return (add(multiply(vec3_(1.0, 1.0, 1.0), 1.0 - t),
				multiply(vec3_(0.5, 0.7, 1.0), t)));
}
*/
t_color	ray_color(const t_ray r, t_hlist *world)
{
	t_hit_record	rec;
	double t = hit(world, r, 0, INFINITY, &rec);
	if (t > 0.0) {
		t_vec3	N = rec.normal;			// N : 법선 단위 벡터
		return (multiply(vec3_(N.x + 1, N.y + 1, N.z + 1), 0.5));	// -1 ≤ N ≤ 1 을 0 과 1 사이의 범위로 변환.
	}
	t_vec3	unit_direction = unit_vector(r.direction);
	t = 0.5 * (unit_direction.y + 1.0);
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

	// World
	t_hlist		*world;

	t_sphere	sphere1 = {(t_point3){0.0, 0.0, -1.0}, 0.5};
	t_sphere	sphere2 = {(t_point3){0.0, -100.5, -1.0}, 100};

	t_hittable	hittable1;
	t_hittable	hittable2;
	hittable1.geometry = _sphere;
	hittable1.pointer = &sphere1;
	hittable2.geometry = _sphere;
	hittable2.pointer = &sphere2;

	push(&world, list_(hittable1));
	push(&world, list_(hittable2));

	// Camera
	double	viewport_height = 2.0;
	double	viewport_width = aspect_ratio * viewport_height;
	int		facal_length = 1.0;

	t_point3 origin = point3_(0, 0, 0);
	t_vec3 horizontal = vec3_(viewport_width, 0, 0);
	t_vec3 vertical = vec3_(0, viewport_height, 0);
	t_vec3 focal = vec3_(0, 0, -facal_length);
	t_vec3 lower_left_corner = add(subtract(focal, origin), add(divide(horizontal, -2), divide(vertical, -2)));

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
	int i, j;
	for (j = img_height - 1; j >= 0 ; j--) {
		// fprintf(stderr, "Scanlines remaining: %d\n", j);	fflush(stderr);
		for (i = 0; i < img_width; i++) {
			double u = (double)i / (img_width - 1);
			double v = (double)(img_height - 1 - j) / (img_height - 1);

			t_ray	r = ray_(origin, \
					add(lower_left_corner, add(multiply(horizontal, u), multiply(vertical, v))), 0);
			t_color pixel_color = ray_color(r, world);
			input_color(&data, pixel_color);
			my_mlx_pixel_put(&data, i, j, data.color);
			// usleep(100000);
		}
	}
	// fprintf(stderr, "\nDone.\n");	fflush(stderr);
	////////////////////////////////////////////////////////////////

	// mlx setting2
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
