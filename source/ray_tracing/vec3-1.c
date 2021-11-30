#include "rtweekend.h"

t_vec3 vec3_(double e1, double e2, double e3)
{
	t_vec3 v;

	v.x = e1;
	v.y = e2;
	v.z = e3;
	return (v);
}

t_vec3 vec3_random()
{
	return (vec3_(random_double(), random_double(), random_double()));
}

t_vec3 vec3_random_(double min, double max)
{
	return (vec3_(random_double_(min,max), random_double_(min,max), random_double_(min,max)));
}

void update(t_vec3 *v, double e1, double e2, double e3)
{
	v->x = e1;
	v->y = e2;
	v->z = e3;
}

t_vec3 negate(t_vec3 v)
{
	return (vec3_(-v.x, -v.y, -v.z));
}
