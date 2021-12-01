#ifndef MOVING_SPHERE_H
# define MOVING_SPHERE_H

#include "rtweekend.h"
#include "hittable.h"

typedef struct s_moving_sphere
{
	t_point3	center0;
	t_point3	center1;
	double		time0;
	double		time1;
	double		radius;
}				t_moving_sphere;

t_hittable	moving_sphere_(t_point3 cen0, t_point3 cen1, double time0, \
						double time1, double radius, t_material material);
int			hit_moving_sphere(t_moving_sphere *s, t_ray *r, double t_min, double t_max, t_hit_record *rec);

#endif