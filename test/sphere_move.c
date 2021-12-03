#include "rtweekend.h"
#include "keycode.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <mlx.h>

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*data;
	int			bpp;
	int			size_l;
	int			endian;
	int			color[3];
}				t_mlx;

t_mlx		mlx;

static void	write_color(t_mlx *mlx, t_color pixel_color, int j, int i, int width)
{

	mlx->color[0] = (int)(255.999 * pixel_color.x) << 16;
	mlx->color[1] = (int)(255.999 * pixel_color.y) << 8;
	mlx->color[2] = (int)(255.999 * pixel_color.z);

	int color = mlx->color[0] + mlx->color[1] + mlx->color[2];
	mlx->data[j * width + i] = mlx_get_color_value(mlx->mlx_ptr, color);
}

static int	hit_sphere(const t_point3 center, double radius, const t_ray r)
{
	t_vec3	oc = subtract(r.origin, center);
	double	a = dot(r.direction, r.direction);
	double	b = 2.0 * dot(oc, r.direction);
	double	c = dot(oc, oc) - (radius * radius);
	double	discriminant = (b * b) - (4 * a * c);
	return (discriminant > 0);
}

static t_color	ray_color(const t_ray* r)
{
	if (hit_sphere((t_point3){0, 0, -1}, 0.5, *r))
		return ((t_color){1, 0, 0});
	t_vec3	unit_direction = unit_vector(r->direction);
	//printf("UNIT_COLOR: %lf %lf %lf\n", unit_direction.x, unit_direction.y, unit_direction.z);
	double	t = 0.5 * (unit_direction.y + 1.0);
	t_color	tmp1 = {1.0, 1.0, 1.0};
	t_color	tmp2 = {0.5, 0.7, 1.0};
	return (add(multiply(tmp1, (1.0 - t)), multiply(tmp2, t)));
}

typedef struct s_data
{
	double		aspect_ratio;
	int			image_width;
	int			image_height;
	double		viewport_height;
	double		viewport_width;
	double		focal_length;

	t_point3	origin;
	double		alpha;
	double		beta;
	double		gamma;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		tmp;
	t_vec3		lower_left_corner;
}				t_data;

static int	draw(void *param)
{
	t_data	*data = (t_data *)param;
	int j = 0;
	while (j < data->image_height)
	{
		int i = 0;
		while (i < data->image_width)
		{
			double	u = (double)i / (data->image_width - 1);
			double	v = (double)(data->image_height - 1 - j) / (data->image_height - 1);
			t_ray		r;
			r.origin = data->origin;
			r.direction = subtract(add(add(data->lower_left_corner, \
						multiply(data->horizontal, u)), multiply(data->vertical, v)), data->origin);
			t_color	pixel_color = ray_color(&r);
			write_color(&mlx, pixel_color, j, i, data->image_width);
			++i;
		}
		j++;
	}
	mlx_put_image_to_window (mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0 );
	return (0);
}

int	key_hook(int keycode, void *param)
{
	t_data	*data = (t_data *)param;
	double	x = data->origin.x;
	double	y = data->origin.y;
	double	z = data->origin.z;

	if (keycode == 53)
		exit(EXIT_SUCCESS);
	if (keycode == ENG_Q)
		update(&(data->origin), x + 0.1, y, z);
	else if (keycode == ENG_A)
		update(&(data->origin), x - 0.1, y, z);
	else if (keycode == ENG_W)
		update(&(data->origin), x, y + 0.1, z);
	else if (keycode == ENG_S)
		update(&(data->origin), x, y - 0.1, z);
	else if (keycode == ENG_E)
		update(&(data->origin), x, y, z + 0.1);
	else if (keycode == ENG_D)
		update(&(data->origin), x, y, z - 0.1);
	else if (keycode == ENG_Z)
	{
		data->alpha++;
		data->tmp.y = sin(degrees_to_radians(data->alpha));
		data->tmp.z = cos(degrees_to_radians(data->alpha));
	}
	else if (keycode == ENG_X)
	{
		data->alpha--;
		data->tmp.y = sin(degrees_to_radians(data->alpha));
		data->tmp.z = cos(degrees_to_radians(data->alpha));
	}
	else if (keycode == ENG_C)
	{
		data->beta++;
		data->tmp.x = sin(degrees_to_radians(data->beta));
		data->tmp.z = cos(degrees_to_radians(data->beta));
	}
	else if (keycode == ENG_V)
	{
		data->beta--;
		data->tmp.x = sin(degrees_to_radians(data->beta));
		data->tmp.z = cos(degrees_to_radians(data->beta));
	}
	data->lower_left_corner = subtract(subtract(subtract(data->origin, divide(data->horizontal, 2)), \
												divide(data->vertical, 2)), data->tmp);
	//printf("%lf %lf %lf %lf %lf\n", data->alpha, data->beta, data->tmp.x, data->tmp.y, data->tmp.z);
	printf("%lf %lf %lf %lf\n", data->beta, data->lower_left_corner.x, data->lower_left_corner.y, data->lower_left_corner.z);
	return (0);
}

int	main()
{
	t_data		data;

	data.aspect_ratio = 16.0 / 9.0;
	data.image_width = 800;
	data.image_height = (int)(data.image_width / data.aspect_ratio);

	
	data.viewport_height = 2.0;
	data.viewport_width = data.aspect_ratio * data.viewport_height;
	data.focal_length = 1.0;

	data.alpha = 0.0;
	data.beta = 0.0;
	data.gamma = 0.0;
	data.origin = (t_point3){0, 0, 0};
	data.horizontal = (t_vec3){data.viewport_width, 0, 0};	// FIXED VALUE
	data.vertical = (t_vec3){0, data.viewport_height, 0};	// FIXED VALUE
	data.tmp = (t_vec3){0, 0, data.focal_length};			// FIXED VALUE
	data.lower_left_corner = subtract(subtract(subtract(data.origin, divide(data.horizontal, 2)), \
												divide(data.vertical, 2)), data.tmp);

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, data.image_width, data.image_height, "rainbow");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, data.image_width, data.image_height);
	mlx.data = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.size_l, &mlx.endian);

	//printf("P3\n%d %d\n255\n", image_width, image_height);
	mlx_key_hook(mlx.win_ptr, &key_hook, &data);
	mlx_loop_hook(mlx.mlx_ptr, &draw, &data);
	mlx_loop(mlx.mlx_ptr);
}