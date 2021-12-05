#include "ray.h"

t_ray	ray_(t_point3 origin, t_vec3 direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

// origin이 시작점인 벡터의 크기가 t 배 되었을 때의 벡터를 반환
t_point3	at(const t_ray *r, double t)
{
	return (add(r->origin, multiply(r->direction, t)));
}
