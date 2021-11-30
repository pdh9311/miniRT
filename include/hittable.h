#ifndef HITTABLE_H
# define HITTABLE_H

# include "rtweekend.h"
# include "material.h"

void set_face_normal(hit_record *rec, ray *r, t_vec3 outward_normal)
{
	rec->front_face = dot(r->direction, outward_normal) < 0;
	rec->normal = rec->front_face ? outward_normal : negate(outward_normal);
}

typedef enum	e_geometry
{
	_sphere,
	_moving_sphere
	
}				t_geometry;

typedef struct	hittable
{
	t_geometry geometry;
	t_material material;
	void *pointer;
}				hittable;

#endif