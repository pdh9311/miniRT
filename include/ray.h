#ifndef RAY_H
# define RAY_H

# include "vec3.h"

typedef struct	ray
{
	point3 origin;
	t_vec3 direction;
	double time;
}				ray;

ray ray_(point3 origin, t_vec3 direction, double time)
{
	ray r;

	r.origin = origin;
	r.direction = direction;
	r.time = time;
	return (r);
}

point3 at(const ray *r, double t)
{
	return (add(r->origin, multiply(r->direction, t)));
}

#endif