#include "sphere.h"
#include "hit.h"

int	hit_sphere(const t_ray *r, t_sphere *sphere, t_hit_record *rec)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	discrimiant;

	oc = subtract(r->origin, sphere->center);
	a = dot(r->direction, r->direction);
	half_b = dot(oc, r->direction);
	c = dot(oc, oc) - (pow(sphere->radius, 2));
	discrimiant = pow(half_b, 2) - (a * c);
	if (discrimiant < 0.0)
		return (FALSE);

	rec->t = (-half_b - sqrt(discrimiant)) / a;
	if (rec->t < rec->tmin || rec->tmax < rec->t)
	{
		rec->t = (-half_b + sqrt(discrimiant)) / a;
		if (rec->t < rec->tmin || rec->tmax < rec->t)
			return (FALSE);
	}
	rec->p = at(r, rec->t);
	rec->normal = unit_vector(subtract(rec->p, sphere->center));
	if (dot(r->direction, rec->normal) > 0)
		rec->normal = negate(rec->normal);
	return (TRUE);	 
}

t_object	sphere_(t_point3 center, double radius)
{
	t_object	h;
	t_sphere	*s;

	h.type = _sphere;
	h.figure = malloc(sizeof(t_sphere));
	if ((s = (t_sphere *)h.figure))
	{
		s->center = center;
		s->radius = radius;
	}
	return (h);
}
