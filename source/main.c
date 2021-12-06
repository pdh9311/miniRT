#include "color.h"

int	hit(const t_ray *r, const t_sphere *sphere)
{
	t_vec3	oc = subtract(r->origin, sphere->center);
	double	a = dot(r->direction, r->direction);
	double	half_b = dot(oc, r->direction);
	double	c = dot(oc, oc) - (pow(sphere->radius, 2));
	double	discrimiant = pow(half_b, 2) - (a * c);	// 판별식
	if (discrimiant < 0.0)
		return (FALSE);
	return (TRUE);	 
}

t_color	ray_color(const t_ray *r, const t_sphere *sphere)
{
	t_color	pixel_color;
	t_vec3	unit_dir;
	double	t;

	if (hit(r, sphere))
	{
		pixel_color = (t_color){1.0, 0.0, 0.0};
		return (pixel_color);
	}
	unit_dir = unit_vector(r->direction);
	t = (r->direction.y + 1) * 0.5;
	pixel_color = add(multiply(color_(1.0, 1.0, 1.0), 1 - t), multiply(color_(0.5, 0.7, 1.0), t));
	return (pixel_color);
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
	for (int y = camera->image_width - 1; y >= 0; --y)
	{
		for (int x = 0; x < camera->image_width; ++x)
		{
			double u = (double)x / camera->image_width;
			double v = (double)(camera->image_height - 1 - y) / camera->image_height;
			t_ray r = ray_(camera->origin, new_ray_dir(camera, u, v));
			t_sphere sphere = (t_sphere){point3_(0.0, 0.0, -1.0), 0.5};
			mlx->pixel_color = ray_color(&r, &sphere);
			write_color(&scene, y, x);
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
}