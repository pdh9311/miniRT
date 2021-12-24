/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:03 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:03 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

int	hit_plane(const t_ray *r, t_plane *plane, t_hit_record *rec)
{
	t_vec3	normal;
	float	check;

	normal = plane->normal;
	check = dot(r->direction, normal);
	if (check < 1e-6)
	{
		check = dot(r->direction, plane->n_normal);
		if (check < 1e-6)
			return (FALSE);
		normal = plane->n_normal;
	}
	rec->t = (dot(subtract(plane->point, r->origin), normal)) \
			/ check;
	if (rec->t < TMIN || TMAX < rec->t)
		return (FALSE);
	rec->p = at(r, rec->t);
	rec->color = plane->color;
	rec->normal = normal;
	if (dot(unit_vector(r->direction), rec->normal) > 0)
		rec->normal = negate(rec->normal);
	return (TRUE);
}

t_object	plane_(t_point3 origin, t_vec3 normal, \
				t_color albedo, t_color color)
{
	t_object	new_pl;
	t_plane		*pl;

	pl = NULL;
	new_pl.type = _plane;
	new_pl.albedo = albedo;
	new_pl.figure = malloc(sizeof(t_plane));
	pl = (t_plane *)new_pl.figure;
	if (pl)
	{
		pl->point = origin;
		pl->normal = unit_vector(normal);
		pl->n_normal = negate(normal);
		pl->color = color;
	}
	return (new_pl);
}
