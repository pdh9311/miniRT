#include "vec3.h"

t_vec3	vec3(double e1, double e2, double e3)
{
	t_vec3	v;

	v.x = e1;
	v.y = e2;
	v.z = e3;
	return (v);
}

void	update(t_vec3 *v, double e1, double e2, double e3)
{
	v->x = e1;
	v->y = e2;
	v->z = e3;
}

double x(t_vec3 v)
{
	return (v.x);
}

double y(t_vec3 v)
{
	return (v.y);
}

double z(t_vec3 v)
{
	return (v.z);
}

t_vec3	negative(t_vec3 v)
{
	return (vec3(-v.x, -v.y, -v.z));
}

////////////////// add ///////////////////
void	add_(t_vec3 *v, t_vec3 u)
{
	update(v, v->x + u.x, v->y + u.y, v->z + u.z);
}

t_vec3	add(t_vec3 v, t_vec3 u)
{
	return (vec3(v.x + u.x, v.y + u.y, v.z + u.z));
}

////////////////// multiply ///////////////////
void	multiply(t_vec3 *v, double t)
{
	v->x *= t;
	v->y *= t;
	v->z *= t;
}

t_vec3	multiply_(t_vec3 v, t_vec3 u)
{
	return (vec3(v.x * u.x, v.y * u.y, v.z * u.z));
}

t_vec3	mutiply__(t_vec3 v, double t)
{
	return (vec3(v.x * t, v.y * t, v.z * t));
}

////////////////// divide ///////////////////
void	divide(t_vec3 *v, double t)
{
	v->x /= t;
	v->y /= t;
	v->z /= t;
}

t_vec3	divide_(t_vec3 v, double t)
{
	return (vec3(v.x / t, v.y / t, v.z / t));
}

////////////////// substract ///////////////////
void	substract_(t_vec3 *v, t_vec3 u)
{
	update(v, v->x - u.x, v->y - u.y, v->z - u.z);
}

t_vec3	substract(t_vec3 v, t_vec3 u)
{
	return (vec3(v.x - u.x, v.y - u.y, v.z - u.z));
}

////////////////// length ///////////////////
double	length_squared(t_vec3 v)
{
	return (pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

double	length(t_vec3 v)
{
	return (sqrt(length_squared(v)));
}

////////////////// near_zero ///////////////////
int	near_zero(t_vec3 v)
{
	double	s;

	s = 1e-8;
	return ((fabs(v.x) < s) && fabs(v.y) < s && fabs(v.z) < s);
}

////////////////// dot ///////////////////
double	dot(t_vec3 *v, t_vec3*u)
{
	return (vec3(v->x * u->x, v->y * u->y, v->z * u->z));
}

////////////////// cross ///////////////////
t_vec3	cross(t_vec3 *v, t_vec3 *u)
{
	return (vec3(v->y * u->z - v->z * u->y, \
				v->z *u->x - v->x * u->z ,	\
				v->x * u->y - v->y * u->x));
}


////////////////// unit_vector ///////////////////
t_vec3	unit_vector(t_vec3 v)
{
	return (divide_(v, length(v)));
}

