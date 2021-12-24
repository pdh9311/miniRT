/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_clamp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:06 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:06 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	deg_to_rad(float degrees)
{
	return (degrees * M_PI / 180.0);
}

float	random_float(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

float	random_float_(float min, float max)
{
	return (min + (max - min) * random_float());
}

float	clamp(float x, float min, float max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
