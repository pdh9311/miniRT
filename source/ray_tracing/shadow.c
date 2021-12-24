/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:10 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:10 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

static int	shadow_hit(t_hlist *current, t_ray *r, t_hit_record *rec, float max)
{
	t_hit_record	temp_rec;
	float			closest_so_far;
	int				hit_anything;
	int				idx;

	hit_anything = FALSE;
	closest_so_far = max;
	idx = 0;
	(void)rec;
	while (current)
	{
		if (hit_(&current->object, r, &temp_rec))
		{
			if (temp_rec.t > TMIN && temp_rec.t < closest_so_far)
			{
				return (TRUE);
			}
		}
		current = current->next;
		++idx;
	}
	return (hit_anything);
}

int	set_shadow(t_scene *scene, t_hit_record *rec, t_phong *phong)
{
	phong->light_len = length(phong->light_dir);
	phong->light_ray = ray_(rec->p, phong->light_unit_dir);
	if (shadow_hit(scene->list, &phong->light_ray, \
			&phong->shadow_rec, phong->light_len))
		return (TRUE);
	return (FALSE);
}
