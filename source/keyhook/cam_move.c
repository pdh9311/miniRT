/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:54:10 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:54:10 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyhook.h"

void	camera_move(t_camera *cam, int keycode)
{
	if (keycode == ENG_D)
		cam->origin = add(cam->origin, multiply(cam->u, cam->move));
	else if (keycode == ENG_A)
		cam->origin = add(cam->origin, multiply(cam->u, -cam->move));
	else if (keycode == ENG_W)
		cam->origin = add(cam->origin, multiply(cam->v, cam->move));
	else if (keycode == ENG_S)
		cam->origin = add(cam->origin, multiply(cam->v, -cam->move));
	else if (keycode == ENG_E)
		cam->origin = add(cam->origin, \
						multiply(unit_vector(cam->vector), -cam->move));
	else if (keycode == ENG_Q)
		cam->origin = add(cam->origin, \
						multiply(unit_vector(cam->vector), cam->move));
}
