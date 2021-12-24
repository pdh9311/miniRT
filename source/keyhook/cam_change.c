/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:54:08 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:54:09 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyhook.h"

void	camera_change(t_scene *scene, int keycode)
{
	if (keycode == ENG_N)
		next_camera(scene);
	else if (keycode == ENG_B)
		previous_camera(scene);
}
