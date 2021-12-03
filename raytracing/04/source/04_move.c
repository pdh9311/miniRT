#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "keyhook.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "minirt.h"

int	hit_sphere(const t_point3 center, double radius, const t_ray r)
{
	t_vec3	oc = subtract(center, r.origin);
	double	a = dot(r.direction, r.direction);
	double	b = 2.0 * dot(oc, r.direction);
	double	c = dot(oc, oc) - (radius * radius);
	double	discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

t_color	ray_color(const t_ray r)
{
	t_point3	center = vec3_(0.0, 0.0, -1.0);
	if (hit_sphere(center, 0.2, r))
		return (vec3_(1, 0, 0));
	t_vec3	unit_direction = unit_vector(r.direction);
	double	t = 0.5 * (unit_direction.y + 1.0);
	return (add(multiply(vec3_(1.0, 1.0, 1.0), 1.0 - t),
				multiply(vec3_(0.5, 0.7, 1.0), t)));
}


int	loop(void *param)
{
	t_data	*data = (t_data *)param;

	int i, j;
	for (j = data->img_height - 1; j >= 0 ; j--) {
		// fprintf(stderr, "Scanlines remaining: %d\n", j);	fflush(stderr);
		for (i = 0; i < data->img_width; i++) {
			double u = (double)i / (data->img_width - 1);
			double v = (double)(data->img_height - 1 - j) / (data->img_height - 1);
			t_ray	r = ray_(data->origin, \
					add(data->lower_left_corner, add(multiply(data->horizontal, u), multiply(data->vertical, v))), \
					0);
			t_color pixel_color = ray_color(r);
			input_color(data, pixel_color);
			my_mlx_pixel_put(data, i, j, data->color);
			// usleep(100000);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_data	data;

	// Image
	data.aspect_ratio = 16.0 / 9.0;
	data.img_height = 450;
	data.img_width = data.img_height * data.aspect_ratio;


	// Camera
	data.viewport_height = 2.0;
	data.viewport_width = data.aspect_ratio * data.viewport_height;
	data.facal_length = 1.0;

	data.alpha = 0.0;
	data.beta = 0.0;
	data.gamma = 0.0;
	data.origin = point3_(0, 0, 0);
	data.horizontal = vec3_(data.viewport_width, 0, 0);
	data.vertical = vec3_(0, data.viewport_height, 0);
	data.focal = vec3_(0, 0, -data.facal_length);
	data.lower_left_corner = add(subtract(data.focal, data.origin), add(divide(data.horizontal, -2), divide(data.vertical, -2)));

	// fprintf(stderr, "%lf %lf %lf \n", lower_left_corner.x, lower_left_corner.y, lower_left_corner.z);

	// mlx setting1
	data.win_height = data.img_height;
	data.win_width = data.img_width;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.win_width, data.win_height, "Tutorial");
	data.img = mlx_new_image(data.mlx, data.img_width, data.img_height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	mlx_hook(data.win, KEY_PRESS, 1L<<0, key_hook, &data);
/*
	//////////////////////////////////////////////////////////////////

	// Render
	int i, j;
	for (j = img_height - 1; j >= 0 ; j--) {
		// fprintf(stderr, "Scanlines remaining: %d\n", j);	fflush(stderr);
		for (i = 0; i < img_width; i++) {
			double u = (double)i / (img_width - 1);
			double v = (double)(img_height - 1 - j) / (img_height - 1);
			fprintf(stderr, "u: %lf, v: %lf\t\t", u, v);
			t_ray	r = ray_(data.origin, \
					add(lower_left_corner, add(multiply(horizontal, u), multiply(vertical, v))), \
					0);
			fprintf(stderr, "ray direction: %lf %lf %lf\n", r.direction.x, r.direction.y, r.direction.z);
			t_color pixel_color = ray_color(r);
			input_color(&data, pixel_color);
			my_mlx_pixel_put(&data, i, j, data.color);
			// usleep(100000);
		}
	}
	fprintf(stderr, "\nDone.\n");	fflush(stderr);
	////////////////////////////////////////////////////////////////
*/
	// mlx setting2
	// mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
