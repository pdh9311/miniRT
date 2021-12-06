#include "miniRT.h"

t_vec3	color_(double e1, double e2, double e3)
{
	t_vec3	v;

	v.x = e1;
	v.y = e2;
	v.z = e3;
	return (v);
}

t_vec3	point3_(double e1, double e2, double e3)
{
	t_vec3	v;

	v.x = e1;
	v.y = e2;
	v.z = e3;
	return (v);
}

t_vec3  random_unit_hemisphere(t_vec3 n)
{
    t_vec3  unit_vector = random_unit_vector();
    if (dot(unit_vector, n) > 0.0)
        return (unit_vector);
    else
        return (negate(unit_vector));
}
