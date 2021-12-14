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
	if (rec->t < TMIN || TMAX < rec->t)
	{
		rec->t = (-half_b + sqrt(discrimiant)) / a;
		if (rec->t < TMIN || TMAX < rec->t)
			return (FALSE);
	}
	rec->p = at(r, rec->t);
	rec->normal = unit_vector(subtract(rec->p, sphere->center));
	if (dot(unit_vector(r->direction), rec->normal) > 0)
		rec->normal = negate(rec->normal);
	rec->color = sphere->color;
	return (TRUE);
}

t_object	sphere_(t_point3 center, double radius, t_color albedo, t_color color)
{
	t_object	new_sp;
	t_sphere	*s;

	s = NULL;
	new_sp.type = _sphere;
	new_sp.albedo = albedo;
	new_sp.figure = malloc(sizeof(t_sphere));
	s = (t_sphere *)new_sp.figure;
	if (s)
	{
		s->center = center;
		s->radius = radius;
		s->color = color;
	}
	return (new_sp);
}
