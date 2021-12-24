/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:58:31 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:58:31 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "vec3.h"
# include "ray.h"
# include "hit.h"

typedef struct s_sphere
{
	t_point3	center;
	float		radius;
	t_color		color;
}				t_sphere;

typedef struct s_hit_sphere
{
	t_vec3		oc;
	float		a;
	float		half_b;
	float		c;
	float		discrimiant;
}				t_hit_sphere;

int			hit_sphere(const t_ray *r, t_sphere *sphere, t_hit_record *rec);
t_object	sphere_(t_point3 center, float radius, \
					t_color albedo, t_color color);

#endif
