#ifndef SPHERE_H
# define SPHERE_H

#include "vec3.h"
#include "hittable.h"

typedef struct	s_sphere
{
	t_point3	center;
	double		radius;
}				t_sphere;

t_hittable	sphere_(t_point3 center, double radius, t_material material)
{
	t_hittable	h;
	t_sphere	*s;

	h.geometry = _sphere;
	h.material = material;
	h.pointer = malloc(sizeof(t_sphere));
	if ((s = (t_sphere *)h.pointer))
	{
		s->center = center;
		s->radius = radius;
	}
	return (h);
}

int	hit_sphere(t_sphere *s, t_ray *r, double t_min, double t_max, t_hit_record *rec)
{
	t_vec3	oc;
	t_vec3	outward_normal;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;
	
	oc = subtract(r->origin, s->center);
	a = length_squared(r->direction);
	half_b = dot(oc, r->direction);
	c = length_squared(oc) - s->radius*s->radius;

	discriminant = half_b*half_b - a*c;
	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);

	root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return (FALSE);
	}

	rec->t = root;
	rec->p = at(r, rec->t);
	outward_normal = divide(subtract(rec->p, s->center), s->radius);
	set_face_normal(rec, r, outward_normal);

	return (TRUE);
}

#endif