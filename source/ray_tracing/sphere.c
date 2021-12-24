/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:13 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:14 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "hit.h"

int	hit_sphere(const t_ray *r, t_sphere *sphere, t_hit_record *rec)
{
	t_hit_sphere	sp;

	sp.oc = subtract(r->origin, sphere->center);
	sp.a = dot(r->direction, r->direction);
	sp.half_b = dot(sp.oc, r->direction);
	sp.c = dot(sp.oc, sp.oc) - (pow(sphere->radius, 2));
	sp.discrimiant = pow(sp.half_b, 2) - (sp.a * sp.c);
	if (sp.discrimiant < 0.0)
		return (FALSE);
	rec->t = (-(sp.half_b) - sqrt(sp.discrimiant)) / sp.a;
	if (rec->t < TMIN || TMAX < rec->t)
	{
		rec->t = (-(sp.half_b) + sqrt(sp.discrimiant)) / sp.a;
		if (rec->t < TMIN || TMAX < rec->t)
			return (FALSE);
	}
	rec->p = at(r, rec->t);
	rec->normal = unit_vector(subtract(rec->p, sphere->center));
	if (dot(unit_vector(r->direction), rec->normal) > 0)
		rec->normal = negate(rec->normal);
	rec->color = sphere->color;
	return (TRUE);
}

t_object	sphere_(t_point3 center, float radius, \
					t_color albedo, t_color color)
{
	t_object	new_sp;
	t_sphere	*s;

	s = NULL;
	new_sp.type = _sphere;
	new_sp.albedo = albedo;
	new_sp.figure = malloc(sizeof(t_sphere));
	s = (t_sphere *)new_sp.figure;
	if (s)
	{
		s->center = center;
		s->radius = radius;
		s->color = color;
	}
	return (new_sp);
}
