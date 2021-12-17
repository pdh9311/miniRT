#include "miniRT.h"

static void	init_mlx(t_scene *scene)
{
	t_mlx		*arg;
	t_camera	*cam;

	arg = &scene->mlx;
	cam = scene->camera;
	arg->mlx_ptr = mlx_init();
	arg->win_ptr = mlx_new_window(arg->mlx_ptr, cam->image_width, \
					cam->image_height, "rainbow");
	arg->img_ptr = mlx_new_image(arg->mlx_ptr, cam->image_width, \
					cam->image_height);
	arg->addr = (char *)mlx_get_data_addr(arg->img_ptr, &arg->bpp, \
					&arg->size_l, &arg->endian);
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
			make_cam_list(scene, (t_element *)(lst->content));
		}
		else if (((t_element *)(lst->content))->type == L)
		{
			make_light_list(scene, (t_element *)(lst->content));
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

void	init(t_scene *scene, t_lst *lst)
{
	scene->list = NULL;
	scene->cam_list = NULL;
	scene->cam_list_move = NULL;
	scene->light_list = NULL;
	scene->light_list_move = NULL;
	make_object_list(scene, lst);
	set_camera(scene);
	set_light(scene);
	init_mlx(scene);
	free_lst(lst);
	// scene->light = (t_light){(t_point3){0.0, 1.0, 1.0}, (t_color){1.0, 1.0, 1.0}, 1.0};
}
