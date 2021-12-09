#include "miniRT.h"

static void	init_camera(t_camera *cam)
{
	cam->aspect_ratio = 16.0 / 9.0;
	cam->image_width = 800;
	cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
	cam->samples_per_pixel = 20;
	cam->focal_length = 1.0;
	cam->vp_height = 2.0;
	cam->vp_width = cam->aspect_ratio * cam->vp_height;
	cam->origin = (t_vec3){0.0, 0.0, 0.0};
	cam->horizontal = (t_vec3){cam->vp_width, 0.0, 0.0};
	cam->vertical = (t_vec3){0.0, cam->vp_height, 0.0};
	cam->focal = (t_vec3){0.0, 0.0, cam->focal_length};
	cam->lower_left_corner = subtract(
			subtract(
				subtract(cam->origin, divide(cam->horizontal, 2)),
				divide(cam->vertical, 2)
				),
			cam->focal
			);
}

static void	init_mlx(t_scene *scene)
{
	t_mlx		*arg;
	t_camera	*cam;

	arg = &scene->mlx;
	cam = &scene->camera;
	arg->mlx_ptr = mlx_init();
	arg->win_ptr = mlx_new_window(arg->mlx_ptr, cam->image_width, \
					cam->image_height, "rainbow");
	arg->img_ptr = mlx_new_image(arg->mlx_ptr, cam->image_width, \
					cam->image_height);
	arg->addr = (char *)mlx_get_data_addr(arg->img_ptr, &arg->bpp, \
					&arg->size_l, &arg->endian);
}

static void	init_ambient(t_light *ambient)
{
	ambient->origin = (t_point3){0.0, 0.0, 0.0};
	ambient->bright_ratio = 1.0;
	ambient->color = (t_color){0.0, 0.0, 0.0}; // change later
}

void	init(t_scene *scene)
{
	init_camera(&scene->camera);
	init_mlx(scene);
	init_ambient(&scene->ambient);
	scene->list = NULL;
	scene->light = (t_light){(t_point3){2.0, 2.0, 1.0}, (t_color){1.0, 1.0, 1.0}, 1.0};
}
