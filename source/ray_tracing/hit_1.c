/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:56:51 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:56:52 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "plane.h"
#include "cylinder.h"

void	init_hit_record(t_hit_record *hit_record)
{
	hit_record->p = (t_point3){0.0, 0.0, 0.0};
	hit_record->normal = (t_point3){0.0, 0.0, 0.0};
	hit_record->t = -1.0;
}

static int	hit_(t_object *object, t_ray *r, t_hit_record *rec)
{
	int	is_hit;

	is_hit = FALSE;
	if (object->type != _none)
	{
		if (object->type == _sphere)
			is_hit = hit_sphere(r, object->figure, rec);
		else if (object->type == _plane)
			is_hit = hit_plane(r, object->figure, rec);
		else if (object->type == _cylinder)
			is_hit = hit_cylinder(r, object->figure, rec);
	}
	if (is_hit)
		rec->albedo = object->albedo;
	return (is_hit);
}

int	hit(t_hlist *current, t_ray *r, t_hit_record *rec, float max)
{
	t_hit_record	temp_rec;
	float			closest_so_far;
	int				hit_anything;

	hit_anything = FALSE;
	closest_so_far = max;
	while (current)
	{
		if (hit_(&current->object, r, &temp_rec))
		{
			if (temp_rec.t < closest_so_far)
			{
				hit_anything = TRUE;
				closest_so_far = temp_rec.t;
				*rec = temp_rec;
			}
		}
		current = current->next;
	}
	return (hit_anything);
}
