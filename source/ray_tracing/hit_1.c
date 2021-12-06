#include "sphere.h"

void	init_hit_record(t_hit_record *hit_record)
{
	hit_record->p = (t_point3){0.0, 0.0, 0.0};
	hit_record->normal = (t_point3){0.0, 0.0, 0.0}; 
	hit_record->t = -1.0;
	hit_record->tmin = 0.001;
	hit_record->tmax = INFINITY;
}

static int	hit_(t_object *object, t_ray *r, t_hit_record *rec)
{
	int	is_hit;

	is_hit = FALSE;
	if (object->type != _none)
	{
		if (object->type == _sphere)
		{
			is_hit = hit_sphere(r, object->figure, rec);
		}
	}
	return (is_hit);
}

int	hit(t_hlist *current, t_ray *r, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	double			closest_so_far;
	int				hit_anything;
	
	hit_anything = FALSE;
	closest_so_far = rec->tmax;
	temp_rec.tmax = rec->tmax;
	temp_rec.tmin = rec->tmin;
	while (current)
	{
		/** 광선을  쏘아서 맞은 지점의 p, normal, t값을 저장해줄텐데 저장할때 
		 * t값이 tmin, tmax에 대한 조건을 만족하면 저장하게 된다.
		 * 
		 */
		if (hit_(&current->object, r, &temp_rec))
			if (temp_rec.t < closest_so_far)
			{
				hit_anything = TRUE;
				closest_so_far = temp_rec.t; 
				*rec = temp_rec;
			}
		current = current->next;
	}
	return (hit_anything);
}