#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define KEY_PRESS 2
#define KEY_RELEASE 3
#define ESC 53

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef t_vec t_point3;
typedef t_vec t_color;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	double	aspect_ratio;

	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	t_vec	color;
	int		trgb;
}	t_data;

typedef struct s_ray
{
	t_point3	orig;		// 원점 좌표
	t_vec		dir;		// 방향 벡터
}	t_ray;

t_vec	vec(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec	vec_add(t_vec v1, t_vec v2)
{
	return (vec(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	return (vec(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vec	vec_mul(t_vec v1, t_vec v2)
{
	return (vec(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}

t_vec	vec_mul_t(t_vec v, double t)
{
	return (vec(v.x * t, v.y * t, v.z * t));
}

t_vec	vec_div_t(t_vec v, double t)
{
	return (vec(v.x / t, v.y / t, v.z /t));
}

///////////////////////////////////////////////////////////

double	length_squared(t_vec e)
{
	return (e.x * e.x + e.y * e.y + e.z * e.z);
}

double	length(t_vec e)
{
	return (sqrt(length_squared(e)));
}

///////////////////////////////////////////////////////////

double	vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	vec_cross(t_vec v1, t_vec v2)
{
	return (v1.y * v2.z - v1.z * v2.y \
			+ v1.z * v2.x - v1.x * v2.z \
			+ v1.x * v2.y - v1.y * v2.x);
}

t_vec	unit_vector(t_vec v)
{
	return (vec_div_t(v, length(v)));
}

///////////////////////////////////////////////////////////

void	white_color(t_data *data, t_vec rgb, int transparency)
{
	int	t = transparency;
	int	r = 255 * rgb.x;
	int g = 255 * rgb.y;
	int b = 255 * rgb.z;

	data->trgb = (t << 24 | r << 16 | g << 8 | b);
}

// 여기서 원점 orig에서 dir 방향으로 t 만큼 이동한 곳의 3차원 상의 좌표를 알 수 있다.
t_vec	ray_at(t_ray ray, double t)
{
	t_vec	tmp;

	tmp.x = ray.orig.x + ray.dir.x * t;
	tmp.y = ray.orig.y + ray.dir.y * t;
	tmp.z = ray.orig.z + ray.dir.z * t;
	return (tmp);
}


double	hit_sphere(t_vec center, double radius, t_ray ray)
{
	t_vec	oc = vec(ray.orig.x - center.x,
					ray.orig.y - center.y,
					ray.orig.z - center.z);
	double	a = vec_dot(ray.dir, ray.dir);
	double	b = 2.0 * vec_dot(oc, ray.dir);
	double	c = vec_dot(oc, oc) - (radius * radius);
	double discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (-1.0);
	return ((-b - sqrt(discriminant)) / (2.0 * a));
}


t_vec	ray_color(t_ray ray)
{
	double	t;

	t = hit_sphere(vec(0, 0, -1), 0.5, ray);
	if (t > 0.0)
	{
		t_vec tmp = ray_at(ray, t);
		t_vec N = unit_vector(vec(tmp.x - 0, tmp.y - 0, tmp.z - (-1)));
		t_vec color = vec_mul_t(vec(N.x + 1, N.y + 1, N.z + 1), 0.5);
		return (color);
	}
	t_vec unit_direction = unit_vector(ray.dir);	// -1 <= unit_direction.y <= 1
	t = 0.5 * (unit_direction.y + 1.0);		// y 값에 따라 t를 만들어 줄건데, color에는 음수값이 없기 때문에 +1 한후 2로 나누어 주었다.
	t_vec	a = vec(1.0, 1.0, 1.0);
	t_vec	b = vec(0.5, 0.7, 1.0);
	return (vec_add(vec_mul_t(a, 1.0 - t), vec_mul_t(b, t)));	// R(t) = (1-t)A + tB
}

///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////

void close(t_data *data)	// 이벤트 발생시 call될 함수
{
	mlx_destroy_window(data->mlx, data->win);	// 창을 닫는다.
	/** [ ADD in Linux or Ubuntu ]
	 * mlx_destroy_image(data->mlx, data->img);
	 * mlx_destroy_display(data->mlx);
	 * free(data->mlx);
	 */
	system("leaks sphere2");	// memory leaks check
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC)
		close(data);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*((unsigned int *)dst) = color;
}


int	main(int ac, char **av)
{
	t_data	data;

	data.aspect_ratio = 16.0 / 9.0;					// 화면 비율
	data.width = 1200;								// 생성할 이미지의 너비
	data.height = data.width / data.aspect_ratio;	// 생성할 이미지의 높이
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.height, "Tutorial 1");
	data.img = mlx_new_image(data.mlx,  data.width, data.height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	mlx_hook(data.win, KEY_PRESS, 1L<<0, key_hook, &data);
	//////////////////////////////////////////////////////////////////

	// Camera	(32/9, 2)
	double	viewport_height = 2.0;									// ray 방향에 있는 viewport의 높이
	double	viewport_width = data.aspect_ratio * viewport_height;	// ray 방향에 있는 viewport의 너비
	double	focal_length = 1.0;										// 초점 거리

	t_vec	origin = vec(0, 0, 0);
	t_vec	horizontal = vec(viewport_width, 0, 0);
	t_vec	vertical = vec(0, viewport_height, 0);
	t_vec	focal = vec(0, 0, focal_length);
	t_vec	lower_left_corner = vec(
		origin.x + (- horizontal.x / 2) + (- vertical.x / 2) ,
		origin.y + (- horizontal.y / 2) + (- vertical.y / 2) ,
		origin.z + (- horizontal.z / 2) + (- vertical.z / 2) + (- focal.z)
	);

	// Render
	int i, j;
	t_ray	ray;
	for (j = 0; j < data.height ; j++)	{
		for (i = 0; i < data.width; i++) {
			double u = (double)i / (data.width - 1);	// 0 <= u < 1
			double v = ((double)data.height - 1 - j) / (data.height - 1);	// 0 <= v < 1
			ray.orig = origin;
			ray.dir = vec(
				lower_left_corner.x + u * horizontal.x + v * vertical.x - origin.x,
				lower_left_corner.y + u * horizontal.y + v * vertical.y - origin.y,
				lower_left_corner.z + u * horizontal.z + v * vertical.z - origin.z
			);
			t_vec pixel_color = ray_color(ray);
			white_color(&data, pixel_color, 0);

			my_mlx_pixel_put(&data, i, j, data.trgb);
		}
	}
	//////////////////////////////////////////////////////////////////
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
