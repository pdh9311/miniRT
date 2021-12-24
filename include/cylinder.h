/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:58:02 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 16:03:28 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "vec3.h"
# include "hit.h"

typedef struct s_cylinder
{
	t_point3	point;
	t_vec3		normal;
	t_vec3		unit_normal;
	float		radius;
	float		height;
	t_color		color;
	t_color		albedo;
}				t_cylinder;

typedef t_cylinder	t_cy_info;

typedef struct s_hit_cy
{
	float	a;
	float	half_b;
	float	c;
	float	discrimiant;
	t_vec3	w;
	float	t1;
	float	t2;
	float	is_between;
}				t_hit_cy;

int			hit_cylinder(const t_ray *r, \
				t_cylinder *cylinder, t_hit_record *rec);
t_object	cylinder_(t_cy_info cy_info);
#endif
