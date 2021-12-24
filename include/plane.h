/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:58:26 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:58:26 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "vec3.h"
# include "ray.h"
# include "hit.h"

typedef struct s_plane
{
	t_point3	point;
	t_vec3		normal;
	t_vec3		n_normal;
	t_color		color;
}				t_plane;

int			hit_plane(const t_ray *r, t_plane *plane, t_hit_record *rec);

t_object	plane_(t_point3 origin, t_vec3 normal, \
					t_color albedo, t_color color);

#endif
