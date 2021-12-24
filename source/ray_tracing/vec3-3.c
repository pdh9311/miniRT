/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3-3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:19 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:19 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	divide(t_vec3 v, float t)
{
	return (multiply(v, 1 / t));
}

float	length_squared(t_vec3 v)
{
	return (v.x * v.x
		+ v.y * v.y
		+ v.z * v.z);
}

float	length(t_vec3 v)
{
	return (sqrt(length_squared(v)));
}

void	add_(t_vec3 *u, t_vec3 v)
{
	update(u, u->x + v.x, u->y + v.y, u->z + v.z);
}

t_vec3	add(t_vec3 u, t_vec3 v)
{
	return (vec3_(u.x + v.x, u.y + v.y, u.z + v.z));
}
