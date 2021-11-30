#include "rtweekend.h"

int	near_zero(t_vec3 v)
{
	double	s;

	s = 1e-8;
	return ((fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s));
}

t_vec3	multiply__(t_vec3 v, t_vec3 u)
{
	return (vec3_(v.x * u.x, v.y * u.y, v.z * u.z));
}

void	multiply_(t_vec3 *v, double t)
{
	v->x *= t;
	v->y *= t;
	v->z *= t;
}

t_vec3	multiply(t_vec3 v, double t)
{
	return (vec3_(v.x * t, v.y * t, v.z * t));
}

void	divide_(t_vec3 *v, double t)
{
	multiply_(v, 1 / t);
}
