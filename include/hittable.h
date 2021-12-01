#ifndef HITTABLE_H
# define HITTABLE_H

# include "rtweekend.h"
# include "material.h"

typedef enum e_geometry
{
	_sphere,
	_moving_sphere
}				t_geometry;

typedef struct s_hittable
{
	t_geometry	geometry;
	t_material	material;
	void		*pointer;
}				t_hittable;

typedef struct s_range
{
	double	t_min;
	double	t_max;
}				t_range;

void	set_face_normal(t_hit_record *rec, t_ray *r, t_vec3 outward_normal);

#endif