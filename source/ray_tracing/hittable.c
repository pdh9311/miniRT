#include "hittable.h"

void	set_face_normal(t_hit_record *rec, t_ray *r, t_vec3 outward_normal)
{
	rec->front_face = dot(r->direction, outward_normal) < 0;
	if (rec->front_face)
		rec->normal = outward_normal;
	else
		rec->normal = negate(outward_normal);
}