#include "ray.h"

t_ray	ray_(t_point3 origin, t_vec3 direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_point3	at(const t_ray *r, double t)
{
	return (add(r->origin, multiply(r->direction, t)));
}

t_vec3	new_ray_dir(t_camera *cam, double u, double v)
{
	t_vec3	ret;

	ret = subtract(
			add(add(multiply(cam->horizontal, u),
					multiply(cam->vertical, v)),
				cam->lower_left_corner), cam->origin);
	return (ret);
}
