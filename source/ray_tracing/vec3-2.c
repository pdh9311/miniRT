/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3-2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:17 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:17 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	near_zero(t_vec3 v)
{
	float	s;

	s = 1e-8;
	return ((fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s));
}

t_vec3	multiply__(t_vec3 v, t_vec3 u)
{
	return (vec3_(v.x * u.x, v.y * u.y, v.z * u.z));
}

void	multiply_(t_vec3 *v, float t)
{
	v->x *= t;
	v->y *= t;
	v->z *= t;
}

t_vec3	multiply(t_vec3 v, float t)
{
	return (vec3_(v.x * t, v.y * t, v.z * t));
}

void	divide_(t_vec3 *v, float t)
{
	multiply_(v, 1 / t);
}
