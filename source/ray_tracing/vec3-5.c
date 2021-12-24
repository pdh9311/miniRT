/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3-5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:23 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:23 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	random_in_unit_sphere(void)
{
	t_vec3	p;

	while (TRUE)
	{
		p = vec3_random_(-1, 1);
		if (length_squared(p) >= 1)
			continue ;
		return (p);
	}
}

t_vec3	random_unit_vector(void)
{
	return (unit_vector(random_in_unit_sphere()));
}

t_vec3	random_in_unit_disk(void)
{
	t_vec3	p;

	while (TRUE)
	{
		p = vec3_(random_float_(-1, 1), random_float_(-1, 1), 0);
		if (length_squared(p) >= 1)
			continue ;
		return (p);
	}
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (add(negate(v), multiply(n, 2 * dot(v, n))));
}

t_vec3	refract(t_vec3 uv, t_vec3 n, float etai_over_etat)
{
	float	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	cos_theta = fmin(dot(negate(uv), n), 1.0);
	r_out_perp = multiply(add(uv, multiply(n, cos_theta)), etai_over_etat);
	r_out_parallel = multiply(n, -sqrt(fabs(1.0 - length_squared(r_out_perp))));
	return (add(r_out_perp, r_out_parallel));
}
