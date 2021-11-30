#ifndef VEC3_H
# define VEC3_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define TRUE	1
# define FALSE	0

typedef struct	s_vec3
{
	double x;
	double y;
	double z;
}				t_vec3;

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

int near_zero(t_vec3 v)
{
	double s = 1e-8;
	return ((fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s));
}

t_vec3 multiply__(t_vec3 v, t_vec3 u)
{
	return (vec3_(v.x*u.x, v.y*u.y, v.z*u.z));
}

void multiply_(t_vec3 *v, double t)
{
	v->x *= t;
	v->y *= t;
	v->z *= t;
}

t_vec3 multiply(t_vec3 v, double t)
{
	return (vec3_(v.x*t, v.y*t, v.z*t));
}

void divide_(t_vec3 *v, double t)
{
	multiply_(v, 1/t);
}

t_vec3 divide(t_vec3 v, double t)
{
	return (multiply(v, 1/t));
}

double length_squared(t_vec3 v)
{
	return (v.x * v.x
			+v.y * v.y
			+v.z * v.z);
}

double length(t_vec3 v)
{
	return (sqrt(length_squared(v)));
}

void add_(t_vec3 *u, t_vec3 v)
{
	update(u, u->x + v.x, u->y + v.y, u->z + v.z);
}

t_vec3 add(t_vec3 u, t_vec3 v)
{
	return (vec3_(u.x + v.x, u.y + v.y, u.z + v.z));
}

void subtract_(t_vec3 *u, t_vec3 v)
{
	update(u, u->x - v.x, u->y - v.y, u->z - v.z);
}

t_vec3 subtract(t_vec3 u, t_vec3 v)
{
	return (vec3_(u.x - v.x, u.y - v.y, u.z - v.z));
}

double dot(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x
			+u.y * v.y
			+u.z * v.z);
}

t_vec3 cross(t_vec3 u, t_vec3 v)
{
	return (vec3_(u.y * v.z - u.z * v.y,
				u.z * v.x - u.x * v.z,
				u.x * v.y - u.y * v.x));
}

t_vec3 unit_vector(t_vec3 v)
{
	return (divide(v, length(v)));
}

t_vec3 random_in_unit_sphere()
{
	while (TRUE)
	{
		t_vec3 p = vec3_random_(-1,1);
		if (length_squared(p) >= 1)
			continue;
		return (p);
	}
}

t_vec3 random_unit_vector()
{
	return (unit_vector(random_in_unit_sphere()));
}

//vec3 random_in_hemisphere(vec3 normal)
//{
//	vec3 in_unit_sphere = random_in_unit_sphere();
//	if (dot(in_unit_sphere, normal) > 0.0)
//		return (in_unit_sphere);
//	else
//		return (negate(in_unit_sphere));
//}

t_vec3 random_in_unit_disk()
{
	while (TRUE)
	{
		t_vec3 p = vec3_(random_double_(-1,1), random_double_(-1,1), 0);
		if (length_squared(p) >= 1)
			continue;
		return (p);
	}
}

t_vec3 reflect(t_vec3 v, t_vec3 n)
{
	return (subtract(v, multiply(n, 2*dot(v,n))));
}

t_vec3 refract(t_vec3 uv, t_vec3 n, double etai_over_etat)
{
	double cos_theta = fmin(dot(negate(uv), n), 1.0);
	t_vec3 r_out_perp = multiply(add(uv, multiply(n, cos_theta)), etai_over_etat);
	t_vec3 r_out_parallel = multiply(n, -sqrt(fabs(1.0 - length_squared(r_out_perp))));
	return (add(r_out_perp, r_out_parallel));
}

t_vec3 (*color_)(double e1, double e2, double e3) = vec3_;
t_vec3 (*point3_)(double e1, double e2, double e3) = vec3_;

typedef t_vec3 point3;
typedef t_vec3 color;

#endif