#include "color.h"

t_color	ray_color(t_scene *scene)
{
	t_color			pixel_color;
	//t_vec3			unit_dir;
	t_hit_record	rec;
	double			t;

	init_hit_record(&rec);
	if (hit(scene->list, &scene->ray, &rec, TMAX))
	{
		pixel_color = multiply(add(rec.normal, (t_vec3){1.0, 1.0, 1.0}), 0.5);

		// ambient
		pixel_color = multiply__(pixel_color, rec.albedo);
		add_(&pixel_color, scene->ambient.color);
		multiply_(&pixel_color, scene->ambient.bright_ratio);
		vec_min(&pixel_color, (t_color){1.0, 1.0, 1.0});

		// diffuse
		t_vec3	light_dir;
		t_vec3	light_unit_dir;
		double	kd;

		light_dir = subtract(scene->light.origin, rec.p);
		light_unit_dir = unit_vector(light_dir);
		kd = fmax(dot(rec.normal, light_unit_dir), 0.0);
		multiply_(&pixel_color, kd);

		/// shadow
		t_ray			light_ray;
		double			light_len;
		t_hit_record	shadow_rec;

		light_len = length(light_dir);
		light_ray = ray_(rec.p, light_unit_dir);
		if (hit(scene->list, &light_ray, &shadow_rec, light_len))
			return ((t_color){0.0, 0.0, 0.0});

		// specular
		t_color	specular;
		double	ksn = 256;	// shininess value
		double	ks = 0.5;	// specular strength
		t_vec3	view_dir;
		t_vec3	reflect_dir;
		double 	spec;

		view_dir = unit_vector(negate(scene->ray.direction));
		reflect_dir = reflect(negate(light_unit_dir), rec.normal);
		spec = pow(fmax(dot(view_dir, reflect_dir), 0.0), ksn);
		specular = multiply(pixel_color, ks * spec);
		add_(&pixel_color, specular);
		vec_min(&pixel_color, (t_color){1.0, 1.0, 1.0});
		return (multiply(multiply__(pixel_color, rec.albedo), scene->light.bright_ratio));
	}
	//unit_dir = unit_vector(scene->ray.direction);
	t = (scene->ray.direction.y + 1) * 0.5;
	pixel_color = add(multiply(color_(1.0, 1.0, 1.0), 1 - t), multiply(color_(0.5, 0.7, 1.0), t));
	return (pixel_color);
}

void	draw(t_scene *scene, t_camera* camera, t_mlx *mlx)
{
	double		u;
	double		v;
	//t_ray		r;

	for (int y = camera->image_height - 1; y >= 0; --y)
	{
		for (int x = 0; x < camera->image_width; ++x)
		{
			u = (double)x / camera->image_width;
			v = (double)(camera->image_height - 1 - y) / camera->image_height;
			//r = ray_(camera->origin, new_ray_dir(camera, u, v));
			scene->ray = ray_(camera->origin, new_ray_dir(camera, u, v));
			//mlx->pixel_color = ray_color(&r, scene->list);
			mlx->pixel_color = ray_color(scene);
			write_color(scene, y, x);
		}
	}
}

void	add_object(t_hlist **list)
{
	t_object object1 = sphere_((t_point3){-0.5, 0.0, -1.0}, 0.5, (t_color){1.0, 1.0, 1.0});
	t_object object2 = sphere_((t_point3){0.0, -100.5, -1.0}, 100.0, (t_color){1.0, 1.0, 1.0});
	t_object object3 = sphere_((t_point3){0.5, 0.0, -1.0}, 0.5, (t_color){1.0, 1.0, 1.0});
	push(list, list_(object1));
	push(list, list_(object2));
	push(list, list_(object3));
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
	printf("%d %d\n", camera->image_height, camera->image_width);
	draw(&scene, camera, mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
}