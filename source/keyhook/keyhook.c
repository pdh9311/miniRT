/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:54:32 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:54:33 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyhook.h"

int	key_hook(int keycode, t_scene *scene)
{
	t_camera	*cam;

	cam = scene->camera;
	if (keycode == ESC)
		close_screen(scene);
	if (keycode == ENG_D || keycode == ENG_A || keycode == ENG_W \
		|| keycode == ENG_S || keycode == ENG_E || keycode == ENG_Q)
		camera_move(cam, keycode);
	else if (keycode == UP || keycode == DOWN || keycode == RIGHT \
		|| keycode == LEFT || keycode == PAGEUP || keycode == PAGEDOWN)
		camera_rotate(cam, keycode);
	else if (keycode == ENG_N || keycode == ENG_B)
		camera_change(scene, keycode);
	else if (keycode == ENG_L || keycode == ENG_K)
		light_change(scene, keycode);
	cam->lower_left_corner = subtract(\
			subtract(subtract(cam->origin, divide(cam->horizontal, 2)), \
			divide(cam->vertical, 2)), cam->w);
	return (0);
}
