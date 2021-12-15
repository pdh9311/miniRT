#include "miniRT.h"

static void	init_camera(t_camera *cam, t_element *elem)
{
	cam->aspect_ratio = 16.0 / 9.0;
	cam->image_width = 800;
	cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
	cam->samples_per_pixel = 20;
	cam->focal_length = 1.0;
	cam->origin = elem->coord;
	cam->focal = multiply(unit_vector(\
			subtract((t_vec3)elem->vector, elem->coord)), cam->focal_length);
	cam->fov = elem->fov;
	cam->vp_height = 2 * cam->focal_length * tan(deg_to_rad(elem->fov / 2));
	cam->vp_width = cam->aspect_ratio * cam->vp_height;
	cam->vup = (t_vec3){0, 1, 0};
	cam->w = unit_vector(subtract(cam->origin, cam->focal));
	cam->u = unit_vector(cross(cam->vup, cam->w));
	cam->v = cross(cam->w, cam->u);
	cam->horizontal = multiply(cam->u, cam->vp_width);
	cam->vertical = multiply(cam->v, cam->vp_height);
	cam->lower_left_corner = subtract(
			subtract(subtract(cam->origin, divide(cam->horizontal, 2)),
				divide(cam->vertical, 2)), cam->w);
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

static void	init_light(t_light *light, t_element *elem)
{
	light->origin = (t_point3)elem->coord;
	light->bright_ratio = elem->brightness;
	light->color = divide((t_color)elem->rgb, 255.999);
}

static void	add_object(t_hlist **list, t_element *elem)
{
	t_object	object;

	if (elem->type == PL)
		object = plane_(elem->coord, unit_vector(elem->vector), (t_color){1, 1, 1}, divide(elem->rgb, 255.999));
	else if (elem->type == SP)
		object = sphere_(elem->coord, elem->diameter / 2.0, (t_color){1, 1, 1}, divide(elem->rgb, 255.999));
	else if (elem->type == CY)
		object = cylinder_(elem->coord, unit_vector(elem->vector), (t_color){1, 1, 1}, divide(elem->rgb, 255.999), elem->diameter / 2, elem->height);
	else
		return ;
	push(list, list_(object));
}

void	make_object_list(t_scene *scene, t_lst *lst)
{
	while (lst != NULL)
	{
		if (((t_element *)(lst->content))->type == A)
		{
			init_light(&scene->ambient, (t_element *)(lst->content));
		}
		else if (((t_element *)(lst->content))->type == C)
		{
			init_camera(&scene->camera, (t_element *)(lst->content));
		}
		else if (((t_element *)(lst->content))->type == L)
		{
			init_light(&scene->light, (t_element *)(lst->content));
		}
		else if (((t_element *)(lst->content))->type == PL
				|| ((t_element *)(lst->content))->type == SP
				|| ((t_element *)(lst->content))->type == CY)
		{
			add_object(&scene->list, (t_element *)(lst->content));
		}
		lst = lst->next;
	}
}

int		free_lst(t_lst *lst)
{
	t_lst	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void	init(t_scene *scene, t_lst *lst)
{
	scene->list = NULL;
	make_object_list(scene, lst);
	init_mlx(scene);
	free_lst(lst);
	// scene->light = (t_light){(t_point3){0.0, 1.0, 1.0}, (t_color){1.0, 1.0, 1.0}, 1.0};
}
