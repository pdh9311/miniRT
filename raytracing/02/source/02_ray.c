#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "keyhook.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"

t_color	ray_color(const t_ray r)
{
	t_vec3	unit_direction = unit_vector(r.direction);
	double	t = 0.5 * (unit_direction.y + 1.0);
	return (add(multiply(vec3_(1.0, 1.0, 1.0), 1.0 - t),
				multiply(vec3_(0.5, 0.7, 1.0), t)));
}

/**
 * 광선이 카메라 위치에서 viewport를 통과하도록 보내고
 * 이 광선들의 방향에서 보이는 색을 계산하는 것이 레이 트레이서의 핵심입니다.
 * 1. 눈(카메라)에서 viewport의 픽셀까지의 광선을 계산한다.
 * 2. 광선이 부딪치는 오브젝트들을 결정한다.
 * 3. 광선이 부딪친 위치의 색을 계산한다.
 *
 * [viewport]
 * 	↳ 높이: 2
 * 	↳ 비율: 16/9
 * 	↳ 초점 길이(카메라와 viewport의 거리): 1
 *
 * 	projection plane: viewport
 * 	projection point: camera(eye)
 * 	focal length: 초점길이
 * 	focus distance: 초점거리
 */
int	main(void)
{
	t_data	data;

	// Image
	double	aspect_ratio = 16.0 / 9.0;
	int		img_height = 225;
	int		img_width = img_height * aspect_ratio;


	// Camera
	double	viewport_height = 2.0;
	double	viewport_width = aspect_ratio * viewport_height;
	int		facal_length = 1.0;

	t_point3 origin = point3_(0, 0, 0);
	t_vec3 horizontal = vec3_(viewport_width, 0, 0);
	t_vec3 vertical = vec3_(0, viewport_height, 0);
	t_vec3 focal = vec3_(0, 0, -facal_length);
	t_vec3 lower_left_corner = add(subtract(focal, origin), add(divide(horizontal, -2), divide(vertical, -2)));
	// t_vec3 lower_left_corner = subtract(subtract(subtract(origin, divide(horizontal, 2)), divide(vertical, 2)), vec3_(0, 0, 1.0));
	fprintf(stderr, "%lf %lf %lf \n", lower_left_corner.x, lower_left_corner.y, lower_left_corner.z);
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
			double v = (double)(img_height - 1 - j) / (img_height - 1);		// ray의 v 값을 점점 증가 시키기 위해서
			fprintf(stderr, "u: %lf, v: %lf\t\t", u, v);
			// ray
			t_ray	r = ray_(origin, \
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

	// mlx setting2
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
