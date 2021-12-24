/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3-4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:21 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:21 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	subtract_(t_vec3 *u, t_vec3 v)
{
	update(u, u->x - v.x, u->y - v.y, u->z - v.z);
}

t_vec3	subtract(t_vec3 u, t_vec3 v)
{
	return (vec3_(u.x - v.x, u.y - v.y, u.z - v.z));
}

float	dot(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x
		+ u.y * v.y
		+ u.z * v.z);
}

t_vec3	cross(t_vec3 u, t_vec3 v)
{
	return (vec3_(u.y * v.z - u.z * v.y,
			u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x));
}

t_vec3	unit_vector(t_vec3 v)
{
	return (divide(v, length(v)));
}
