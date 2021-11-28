#include "mlx.h"
#include <stdio.h>
#include <math.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

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
	int		int_color;
}	t_data;

t_vec	vec(double e1, double e2, double e3)
{
	t_vec	v;

	v.x = e1;
	v.y = e2;
	v.z = e3;
	return (v);
}

t_vec	vec_mul_n(t_vec v, double n)
{
	t_vec	tmp;

	tmp.x = v.x * n;
	tmp.y = v.y * n;
	tmp.z = v.z * n;
	return (tmp);
}

t_vec	vec_mul(t_vec v1, t_vec v2)
{
	t_vec	tmp;

	tmp.x = v1.x * v2.x;
	tmp.y = v1.y * v2.y;
	tmp.z = v1.z * v2.z;
	return (tmp);
}

double	dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec	tmp;

	tmp.x = v1.x - v2.x;
	tmp.y = v1.y - v2.y;
	tmp.z = v1.z - v2.z;
	return (tmp);
}

t_vec	vec_add(t_vec v1, t_vec v2)
{
	t_vec	tmp;

	tmp.x = v1.x + v2.x;
	tmp.y = v1.y + v2.y;
	tmp.z = v1.z + v2.z;
	return (tmp);
}

t_vec	vec_div(t_vec v1, double n)
{
	t_vec	tmp;

	tmp.x = v1.x / n;
	tmp.y = v1.y / n;
	tmp.z = v1.z / n;
	return (tmp);
}

void	white_color(t_data *data, t_vec c)
{
	int	ir = 255.999 * c.x;
	int ig = 255.999 * c.y;
	int ib = 255.999 * c.z;

	data->color.x = ir << 16;
	data->color.y = ig << 8;
	data->color.z = ib;
	data->int_color = data->color.x + data->color.y + data->color.z;
}

double	length_squared(t_vec e)
{
	return (e.x * e.x + e.y * e.y + e.z * e.z);
}

double	length(t_vec e)
{
	return (sqrt(length_squared(e)));
}

t_vec	unit_vector(t_vec v)
{
	return (vec_div(v, length(v)));
}

// R(t) = (1 - t)A + tB
t_vec	ray_color(t_vec orig, t_vec dir)
{
	t_vec	unit_direction = unit_vector(dir);
	double	t = 0.5 * (unit_direction.y + 1.0);			//
	t_vec	a = vec(1.0, 1.0, 1.0);
	t_vec	b = vec(0.5, 0.7, 1.0);
	return (vec_add(vec_mul_n(a, 1.0 - t), vec_mul_n(b, t)));
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*((unsigned int *)dst) = color;
}

int	main(void)
{
	t_data	data;

	data.aspect_ratio = 16.0 / 9.0;
	data.width = 400;
	data.height = data.width / data.aspect_ratio;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.height, "Tutorial 1");
	data.img = mlx_new_image(data.mlx,  data.width, data.height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	//////////////////////////////////////////////////////////////////

	// Camera
	double	viewport_height = 2.0;
	double	viewport_width = data.aspect_ratio * viewport_height;
	double	focal_length = 1.0;


	t_vec	origin = vec(0, 0, 0);
	t_vec	horizontal = vec(viewport_width, 0, 0);
	t_vec	vertical = vec(0, viewport_height, 0);
	t_vec	any = vec(0, 0, focal_length);
	t_vec	lower_left_corner = vec_sub( \
						origin, \
						vec_add(vec_add(vec_div(horizontal, 2), vec_div(vertical, 2)), any) \
						);
	// Render
	int i, j;
	for (j = 0; j < data.height ; j++)	{
		for (i = 0; i < data.width; i++) {
			double u = (double)i / (data.width - 1);
			double v = (data.height - (double)j - 1) / (data.height - 1);

			t_vec a = origin;
			t_vec b = vec_add( \
					lower_left_corner, \
					vec_add(vec_mul_n(horizontal, u), vec_mul_n(vec_sub(vertical, origin), v)) \
					);
			t_vec pixel_color = ray_color(a, b);
			white_color(&data, pixel_color);
			my_mlx_pixel_put(&data, i, j, data.int_color);
		}
	}
	////////////////////////////////////////////////////////////////
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}

