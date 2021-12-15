#include "color.h"
#include "list.h"
#include "keyhook.h"

t_color	ray_color(t_scene *scene)
{
	t_color			pixel_color;
	t_hit_record	rec;
	double			t;
	t_phong			phong;

	init_hit_record(&rec);
	if (hit(scene->list, &scene->ray, &rec, TMAX))
	{
		pixel_color = rec.color;
		set_ambient(&pixel_color, scene, &rec);
		set_diffuse(&pixel_color, scene, &rec, &phong);
		if (set_shadow(scene, &rec, &phong))
			multiply_(&pixel_color, 0.3);
		set_specular(&pixel_color, scene, &rec, &phong);
		return (multiply(multiply__(pixel_color, rec.albedo), scene->light.bright_ratio));
	}
	t = (scene->ray.direction.y + 1) * 0.5;
	pixel_color = add(multiply(color_(1.0, 1.0, 1.0), 1 - t), multiply(color_(0.5, 0.7, 1.0), t));
	return (pixel_color);
}

int	draw(void *param)
{
	double		u;
	double		v;
	t_scene		*scene;

	scene = param;
	for (int y = scene->camera.image_height - 1; y >= 0; --y)
	{
		for (int x = 0; x < scene->camera.image_width; ++x)
		{
			u = (double)x / scene->camera.image_width;
			v = (double)(scene->camera.image_height - 1 - y) / scene->camera.image_height;
			scene->ray = ray_(scene->camera.origin, new_ray_dir(&scene->camera, u, v));
			scene->mlx.pixel_color = ray_color(scene);
			write_color(scene, y, x);
		}
	}
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr, scene->mlx.img_ptr, 0, 0);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	t_scene		scene;
	t_camera	*camera;
	t_mlx		*mlx;

	t_lst		*lst;

	if (argc != 2)
		return (1);
	camera = &scene.camera;
	mlx = &scene.mlx;
	lst = NULL;
	readfile(argv[1], &lst);
	init(&scene, lst);
	printf("%d %d\n", camera->image_height, camera->image_width);
	mlx_hook(mlx->win_ptr, KEY_PRESS, 1L<<0, key_hook, &scene);
	mlx_loop_hook(mlx->mlx_ptr, &draw, &scene);
	mlx_loop(mlx->mlx_ptr);
}
