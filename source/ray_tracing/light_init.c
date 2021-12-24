/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:00 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:01 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_light(t_light *light, t_element *elem)
{
	light->origin = (t_point3)elem->coord;
	light->bright_ratio = elem->brightness;
	light->color = divide((t_color)elem->rgb, 255.999);
}

void	set_light(t_scene *scene)
{
	t_light	**light;
	t_lst	**light_list_move_tmp;

	light = &scene->light;
	light_list_move_tmp = &scene->light_list_move;
	*light_list_move_tmp = scene->light_list;
	*light = (t_light *)scene->light_list_move->content;
}

// add only *** 1 light ***
int	make_light_list(t_scene *scene, t_element *elem)
{
	t_light	*light;
	t_lst	*new_light;
	t_lst	**light_list_tmp;

	light = (t_light *)malloc(sizeof(t_light));
	if (light == NULL)
		return (EXIT_FAILURE);
	init_light(light, elem);
	light_list_tmp = &(scene->light_list);
	new_light = pp_lstnew((void *)light);
	pp_lstadd_back(light_list_tmp, new_light);
	return (EXIT_SUCCESS);
}

void	next_light(t_scene *scene)
{
	t_light	**light;
	t_lst	**light_list_move_tmp;

	light = &scene->light;
	light_list_move_tmp = &scene->light_list_move;
	if (scene->light_list_move->next == NULL)
		*light_list_move_tmp = scene->light_list;
	else
		*light_list_move_tmp = scene->light_list_move->next;
	*light = (t_light *)scene->light_list_move->content;
}

void	previous_light(t_scene *scene)
{
	t_light	**light;
	t_lst	**light_list_move_tmp;

	light = &scene->light;
	light_list_move_tmp = &scene->light_list_move;
	if (scene->light_list_move->prev == NULL)
		*light_list_move_tmp = pp_lstlast(scene->light_list);
	else
		*light_list_move_tmp = scene->light_list_move->prev;
	*light = (t_light *)scene->light_list_move->content;
}
