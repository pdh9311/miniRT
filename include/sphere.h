#ifndef SPHERE_H
# define SPHERE_H

# include "vec3.h"
# include "ray.h"

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
}				t_sphere;

#endif