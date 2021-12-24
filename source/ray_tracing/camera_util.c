/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:54:58 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:54:59 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	previous_camera(t_scene *scene)
{
	t_camera	**cam;
	t_lst		**cam_list_move_tmp;

	cam = &scene->camera;
	cam_list_move_tmp = &scene->cam_list_move;
	if (scene->cam_list_move->prev == NULL)
		*cam_list_move_tmp = pp_lstlast(scene->cam_list);
	else
		*cam_list_move_tmp = scene->cam_list_move->prev;
	*cam = (t_camera *)scene->cam_list_move->content;
}

void	next_camera(t_scene *scene)
{
	t_camera	**cam;
	t_lst		**cam_list_move_tmp;

	cam = &scene->camera;
	cam_list_move_tmp = &scene->cam_list_move;
	if (scene->cam_list_move->next == NULL)
		*cam_list_move_tmp = scene->cam_list;
	else
		*cam_list_move_tmp = scene->cam_list_move->next;
	*cam = (t_camera *)scene->cam_list_move->content;
}

int	free_cameras(t_lst *cam_list)
{
	t_lst	*tmp;

	if (cam_list == NULL)
		return (EXIT_FAILURE);
	while (cam_list != NULL)
	{
		tmp = cam_list->next;
		free(cam_list->content);
		free(cam_list);
		cam_list = tmp;
	}
	return (EXIT_SUCCESS);
}
