#ifndef HITTABLE_H
# define HITTABLE_H

# include "rtweekend.h"
# include "material.h"
# include "vec3.h"

typedef enum e_geometry
{
	_sphere,
	_moving_sphere
}	t_geometry;

typedef struct s_hittable
{
	t_geometry	geometry;
	t_material	material;
	void		*pointer;
}	t_hittable;

void	set_face_normal(t_hit_record *rec, t_ray *r, t_vec3 outward_normal);
#endif
