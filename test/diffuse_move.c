#include "miniRT.h"
#include "color.h"
#include "keycode.h"
#include "hittable_list.h"
#include "miniRT.h"
#include "sphere.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <mlx.h>

typedef struct s_data
{
	float		aspect_ratio;
	int			image_width;
	int			image_height;
	int			samples_per_pixel;
	int			depth;
	float		viewport_height;
	float		viewport_width;
	float		focal_length;

	t_point3	origin;
	float		alpha;
	float		beta;
	float		gamma;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		tmp;
	t_vec3		lower_left_corner;
	t_hlist		*world;
}				t_data;

t_mlx		mlx;

t_color	ray_color(t_ray* r, t_hlist *world, int depth)
{
	t_hit_record	rec;
	t_vec3			unit_direction;
	float			t;
	t_color			tmp1;
	t_color			tmp2;

	if (depth <= 0)
		return ((t_color){0.0, 0.0, 0.0});
	if (hit(world, r, (t_range){0.001, INFINITY}, &rec))
	{
		t_point3	target = add(add(rec.p, rec.normal), random_in_unit_sphere());
		t_ray		tmp = {rec.p, subtract(target, rec.p), 0.0};
		return (multiply(ray_color(&tmp, world, depth - 1), 0.5));
		//return ((multiply(add(rec.normal, (t_color){1.0, 1.0, 1.0}), 0.5)));
	}
	unit_direction = unit_vector(r->direction);
	t = 0.5 * (unit_direction.y + 1.0);
	tmp1 = (t_color){1.0, 1.0, 1.0};
	tmp2 = (t_color){0.5, 0.7, 1.0};
	return (add(multiply(tmp1, (1.0 - t)), multiply(tmp2, t)));
}

static int	draw(void *param)
{
	t_data	*data = (t_data *)param;
	int j = 0;
	while (j < data->image_height)
	{
		int i = 0;
		while (i < data->image_width)
		{
			t_color	pixel_color = {0.0, 0.0, 0.0};
			for (int s = 0; s < data->samples_per_pixel; ++s)
			{
				float	u = ((i + random_float()) / (data->image_width - 1));
				float	v = ((data->image_height - 1 - j + random_float()) / (data->image_height - 1));
				t_ray		r;
				r.origin = data->origin;
				r.direction = subtract(add(add(data->lower_left_corner, multiply(data->horizontal, u)), \
									multiply(data->vertical, v)), data->origin);
				add_(&pixel_color, ray_color(&r, data->world, data->depth));
			}
			write_color(&mlx, pixel_color, (j * data->image_width + i), data->samples_per_pixel);
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
	float	x = data->origin.x;
	float	y = data->origin.y;
	float	z = data->origin.z;

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
	data.samples_per_pixel = 1;
	data.world = NULL;
	data.depth = 50;


	data.viewport_height = 2.0;
	data.viewport_width = data.aspect_ratio * data.viewport_height;
	data.focal_length = 1.0;

	t_sphere		sphere1 = {(t_point3){0.0, 0.0, -1.0}, 0.5};
	t_sphere		sphere2 = {(t_point3){0.0, -100.5, -1.0}, 100.0};
	t_object		hittable1;
	t_object		hittable2;

	hittable1.geometry = _sphere;
	hittable1.pointer = &sphere1;
	hittable2.geometry = _sphere;
	hittable2.pointer = &sphere2;

	push(&data.world, list_(hittable1));
	push(&data.world, list_(hittable2));

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
