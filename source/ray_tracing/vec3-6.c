/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3-6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:25 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:25 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	color_(float e1, float e2, float e3)
{
	t_vec3	v;

	v.x = e1;
	v.y = e2;
	v.z = e3;
	return (v);
}

t_vec3	point3_(float e1, float e2, float e3)
{
	t_vec3	v;

	v.x = e1;
	v.y = e2;
	v.z = e3;
	return (v);
}

t_vec3	random_unit_hemisphere(t_vec3 n)
{
	t_vec3	unit_vector;

	unit_vector = random_unit_vector();
	if (dot(unit_vector, n) > 0.0)
		return (unit_vector);
	else
		return (negate(unit_vector));
}

void	vec_min(t_vec3 *v, t_vec3 max)
{
	if (v->x >= max.x)
		v->x = max.x;
	if (v->y >= max.y)
		v->y = max.y;
	if (v->z >= max.z)
		v->z = max.z;
}
