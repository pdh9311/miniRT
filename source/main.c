#include "color.h"

t_color	ray_color(t_ray *r, t_hlist *list)
{
	t_color			pixel_color;
	t_vec3			unit_dir;
	t_hit_record	rec;
	double			t;

	init_hit_record(&rec);
	if (hit(list, r, &rec))
	{
		pixel_color = multiply(add(rec.normal, (t_vec3){1.0, 1.0, 1.0}), 0.5);
		return (pixel_color);
	}
	unit_dir = unit_vector(r->direction);
	t = (r->direction.y + 1) * 0.5;
	pixel_color = add(multiply(color_(1.0, 1.0, 1.0), 1 - t), multiply(color_(0.5, 0.7, 1.0), t));
	return (pixel_color);
}

void	draw(t_scene *scene, t_camera* camera, t_mlx *mlx)
{
	double		u;
	double		v;
	t_ray		r;

	for (int y = camera->image_width - 1; y >= 0; --y)
	{
		for (int x = 0; x < camera->image_width; ++x)
		{
			u = (double)x / camera->image_width;
			v = (double)(camera->image_height - 1 - y) / camera->image_height;
			r = ray_(camera->origin, new_ray_dir(camera, u, v));
			mlx->pixel_color = ray_color(&r, scene->list);
			write_color(scene, y, x);
		}
	}
}

void	add_object(t_hlist **list)
{
	t_object object1 = sphere_((t_point3){0.0, 0.0, -1.0}, 0.5);
	t_object object2 = sphere_((t_point3){0.0, -100.5, -1.0}, 100.0);
	push(list, list_(object1));
	push(list, list_(object2));
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_scene		scene;
	t_camera	*camera;
	t_mlx		*mlx;

	init(&scene);
	camera = &scene.camera;
	mlx = &scene.mlx;
	add_object(&scene.list);
	draw(&scene, camera, mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
}