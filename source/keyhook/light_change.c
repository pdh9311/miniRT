/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:54:37 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:54:37 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyhook.h"

void	light_change(t_scene *scene, int keycode)
{
	if (keycode == ENG_L)
		next_light(scene);
	else if (keycode == ENG_K)
		previous_light(scene);
}
