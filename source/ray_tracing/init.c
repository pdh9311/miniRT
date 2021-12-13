#include "miniRT.h"

static void	init_camera(t_camera *cam, t_element *elem)
{
	cam->aspect_ratio = 16.0 / 9.0;
	cam->image_width = 800;
	cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
	cam->samples_per_pixel = 20;
	cam->focal_length = 1.0;
	cam->focal = multiply(unit_vector((t_vec3)elem->vector), cam->focal_length);	////
	cam->origin = elem->coord;			///
	cam->fov = elem->fov;
	cam->vp_height = 2 * cam->focal_length * tan(degrees_to_radian(elem->fov / 2));
	cam->vp_width = cam->aspect_ratio * cam->vp_height;
	cam->vup = (t_vec3){0, 1, 0};
	cam->w = unit_vector(subtract(cam->origin, cam->focal));
	cam->u = unit_vector(cross(cam->vup, cam->w));
	cam->v = cross(cam->w, cam->u);
	cam->horizontal = multiply(cam->u, cam->vp_width);
	cam->vertical = multiply(cam->v, cam->vp_height);
	cam->lower_left_corner = subtract(
			subtract(
				subtract(cam->origin, divide(cam->horizontal, 2)),
				divide(cam->vertical, 2)
				),
				cam->w
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

void	tmp(t_scene *scene, t_lst *lst)
{
	while (lst != NULL)
	{
		if (((t_element *)(lst->content))->type == A)
		{

		} else if (((t_element *)(lst->content))->type == C)
		{
			init_camera(&scene->camera, (t_element *)(lst->content));
		} else if (((t_element *)(lst->content))->type == L)
		{

		} else if (((t_element *)(lst->content))->type == PL)
		{

		} else if (((t_element *)(lst->content))->type == SP)
		{

		} else if (((t_element *)(lst->content))->type == CY)
		{

		}
		lst = lst->next;
	}
}

void	init(t_scene *scene, t_lst *lst)
{
	init_camera(&scene->camera, lst);
	init_mlx(scene);
	init_ambient(&scene->ambient);
	scene->list = NULL;
	scene->light = (t_light){(t_point3){2.0, 2.0, 1.0}, (t_color){1.0, 1.0, 1.0}, 1.0};
}
