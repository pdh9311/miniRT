#include "ray.h"

t_ray ray_(t_point3 origin, t_vec3 direction, double time)
{
	t_ray r;

	r.origin = origin;
	r.direction = direction;
	r.time = time;
	return (r);
}

t_point3 at(const t_ray *r, double t)
{
	return (add(r->origin, multiply(r->direction, t)));
}