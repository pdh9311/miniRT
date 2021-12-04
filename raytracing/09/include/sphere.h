#ifndef SPHERE_H
# define SPHERE_H

# include "vec3.h"
# include "hittable.h"

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
}	t_sphere;

t_hittable	sphere_(t_point3 center, double radius, t_material material);
int			hit_sphere(t_sphere *s, t_ray r, double t_min, double t_max, t_hit_record *rec);
#endif
