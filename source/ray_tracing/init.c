/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:56:58 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 17:51:12 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_mlx(t_scene *scene)
{
	t_mlx		*arg;
	t_camera	*cam;

	arg = &scene->mlx;
	cam = scene->camera;
	arg->mlx_ptr = mlx_init();
	arg->win_ptr = mlx_new_window(arg->mlx_ptr, cam->image_width, \
					cam->image_height, "miniRT");
	arg->img_ptr = mlx_new_image(arg->mlx_ptr, cam->image_width, \
					cam->image_height);
	arg->addr = (char *)mlx_get_data_addr(arg->img_ptr, &arg->bpp, \
					&arg->size_l, &arg->endian);
}

static void	set_cy_info(t_element *elem, t_cy_info *cy_info)
{
	cy_info->point = elem->coord;
	cy_info->normal = unit_vector(elem->vector);
	cy_info->albedo = (t_color){1, 1, 1};
	cy_info->color = divide(elem->rgb, 255.999);
	cy_info->radius = elem->diameter / 2;
	cy_info->height = elem->height;
}

static void	add_object(t_hlist **list, t_element *elem)
{
	t_object	object;
	t_cy_info	cy_info;

	if (elem->type == PL)
		object = plane_(elem->coord, unit_vector(elem->vector), \
				(t_color){1, 1, 1}, divide(elem->rgb, 255.999));
	else if (elem->type == SP)
		object = sphere_(elem->coord, elem->diameter / 2.0, \
				(t_color){1, 1, 1}, divide(elem->rgb, 255.999));
	else if (elem->type == CY)
	{
		set_cy_info(elem, &cy_info);
		object = cylinder_(cy_info);
	}
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
}
