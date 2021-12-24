/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:30 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:31 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

int	check_rgb(t_color rgb)
{
	if (rgb.x < 0 || rgb.x > 255)
		return (EXIT_FAILURE);
	if (rgb.y < 0 || rgb.y > 255)
		return (EXIT_FAILURE);
	if (rgb.z < 0 || rgb.z > 255)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_ratio(float ratio)
{
	if (ratio < 0.0 || ratio > 1.0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_axis(t_vec3 axis)
{
	if (axis.x < -1.0 || axis.x > 1.0)
		return (EXIT_FAILURE);
	if (axis.y < -1.0 || axis.y > 1.0)
		return (EXIT_FAILURE);
	if (axis.z < -1.0 || axis.z > 1.0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_fov(float fov)
{
	if (fov < 0 || fov > 180)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
