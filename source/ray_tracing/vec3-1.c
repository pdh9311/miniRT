#include "miniRT.h"

t_vec3	vec3_(float e1, float e2, float e3)
{
	t_vec3	v;

	v.x = e1;
	v.y = e2;
	v.z = e3;
	return (v);
}

t_vec3	vec3_random(void)
{
	return (vec3_(random_float(), random_float(), random_float()));
}

t_vec3	vec3_random_(float min, float max)
{
	return (vec3_(random_float_(min, max), \
			random_float_(min, max), random_float_(min, max)));
}

void	update(t_vec3 *v, float e1, float e2, float e3)
{
	v->x = e1;
	v->y = e2;
	v->z = e3;
}

t_vec3	negate(t_vec3 v)
{
	return (vec3_(-v.x, -v.y, -v.z));
}
