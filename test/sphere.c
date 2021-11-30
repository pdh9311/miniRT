#include "rtweekend.h"
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

void	write_color(t_mlx *mlx, color pixel_color, int j, int i, int width)
{

	mlx->color[0] = (int)(255.999 * pixel_color.x) << 16;
	mlx->color[1] = (int)(255.999 * pixel_color.y) << 8;
	mlx->color[2] = (int)(255.999 * pixel_color.z);

	int color = mlx->color[0] + mlx->color[1] + mlx->color[2];
	mlx->data[j * width + i] = mlx_get_color_value(mlx->mlx_ptr, color);
}

int	hit_sphere(const point3 center, double radius, const ray r)
{
	t_vec3	oc = subtract(r.origin, center);
	double	a = dot(r.direction, r.direction);
	double	b = 2.0 * dot(oc, r.direction);
	double	c = dot(oc, oc) - (radius * radius);
	double	discriminant = (b * b) - (4 * a * c);
	return (discriminant > 0);
}

color	ray_color(const ray* r)
{
	if (hit_sphere((point3){0, 0, -1}, 0.5, *r))
		return ((color){1, 0, 0});
	t_vec3	unit_direction = unit_vector(r->direction);
	//printf("UNIT_COLOR: %lf %lf %lf\n", unit_direction.x, unit_direction.y, unit_direction.z);
	double	t = 0.5 * (unit_direction.y + 1.0);
	color	tmp1 = {1.0, 1.0, 1.0};
	color	tmp2 = {0.5, 0.7, 1.0};
	return (add(multiply(tmp1, (1.0 - t)), multiply(tmp2, t)));
}

int	main()
{
	t_mlx		mlx;

	const double	aspect_ratio = 16.0 / 9.0;
	const int		image_width = 800;
	const int		image_height = (int)(image_width / aspect_ratio);

	// Camera
	double			viewport_height = 2.0;
	double			viewport_width = aspect_ratio * viewport_height;
	double			focal_length = 1.0;

	point3			origin = {0, 0, 0};
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
			double	u = (double)i / (image_width - 1);
			double	v = (double)(image_height - 1 - j) / (image_height - 1);
			ray		r;
			r.origin = origin;
			r.direction = subtract(add(add(lower_left_corner, multiply(horizontal, u)), multiply(vertical, v)), origin);
			color	pixel_color = ray_color(&r);
			write_color(&mlx, pixel_color, j, i, image_width);
			++i;
		}
		j++;
	}
	fprintf(stderr, "\nDone\n");
	mlx_put_image_to_window ( mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0 );
	mlx_loop(mlx.mlx_ptr);
}