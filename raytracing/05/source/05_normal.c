#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "keyhook.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <math.h>

/** 광선이 구와 만나는 가장 가까운 위치의 교차점 에서의 t값을 계산
 * 	t^2 b·b + 2 b·(A-C)t +(A-C)·(A-C)-r^2 = 0
 * 	(A-C) → oc
 */
/*
	double	hit_sphere(const t_point3 center, double radius, const t_ray r)
	{
		t_vec3	oc = subtract(r.origin, center);
		double	a = dot(r.direction, r.direction);
		double	b = 2.0 * dot(r.direction, oc);
		double	c = dot(oc, oc) - (radius * radius);
		double	discriminant = (b * b) - (4 * a * c);
		if (discriminant < 0)
			return (-1.0);
		else
			return ((-b - sqrt(discriminant)) / (2.0 * a));
	}
*/
double	hit_sphere(const t_point3 center, double radius, const t_ray r)
{
	t_vec3	oc = subtract(r.origin, center);
	double	a = dot(r.direction, r.direction);
	double	half_b = dot(r.direction, oc);
	double	c = dot(oc, oc) - (radius * radius);
	double	discriminant = (half_b * half_b) - (a * c);
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-half_b - sqrt(discriminant)) / a);
}

t_color	ray_color(const t_ray r)
{
	t_point3	center = vec3_(0.0, 0.0, -1.0);
	double		t = hit_sphere(center, 0.5, r);
	if (t > 0.0) {
		t_vec3	P = at(&r, t);
		t_vec3	N = unit_vector(subtract(P, center));				// N : 법선 단위 벡터
		return (multiply(vec3_(N.x + 1, N.y + 1, N.z + 1), 0.5));	// -1 ≤ N ≤ 1 을 0 과 1 사이의 범위로 변환.
	}
	t_vec3	unit_direction = unit_vector(r.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	return (add(multiply(vec3_(1.0, 1.0, 1.0), 1.0 - t),
				multiply(vec3_(0.5, 0.7, 1.0), t)));
}

/**
 * 법선 벡터를 시각화하는 일반적인 트릭은 법선 벡터의 각 성분을 0에서 1의 범위로 매핑한 다음,
 * 매핑된 법선 벡터의 성분 x/y/z를 r/g/b로 다시 매핑하는 것입니다.
 * ( n(법선 벡터)이 단위 길이 벡터라고 가정하는 것이 쉽고 직관적이기 때문입니다. 그러므로 단위 길이 법선 벡터의 각 성분은 -1 ~ 1사이의 값입니다. )
 * 법선 벡터를 구하기 위해서는 단지 교차하는지가 아닌 교차점이 필요합니다.
 */
int	main(void)
{
	t_data	data;

	// Image
	double	aspect_ratio = 16.0 / 9.0;
	int		img_height = 450;
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
	// fprintf(stderr, "%lf %lf %lf\n", lower_left_corner.x, lower_left_corner.y, lower_left_corner.z);

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
			t_color pixel_color = ray_color(r);
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
