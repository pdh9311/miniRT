#include "moving_sphere.h"

t_hittable moving_sphere_(t_point3 cen0, t_point3 cen1, double time0, double time1, double radius, t_material material)
{
	t_hittable		h;
	t_moving_sphere	*s;

	h.geometry = _moving_sphere;
	h.material = material;
	h.pointer = malloc(sizeof(t_moving_sphere));
	if ((s = (t_moving_sphere *)h.pointer))
	{
		s->center0 = cen0;
		s->center1 = cen1;
		s->time0 = time0;
		s->time1 = time1;
		s->radius = radius;
	}
	return (h);
}

static t_point3	center(t_moving_sphere *s, double time)
{
	t_point3	center;

	center = subtract(s->center1, s->center0);
		multiply_(&center, (time - s->time0) / (s->time1 - s->time0));
		add_(&center, s->center0);
	return (center);
}

int hit_moving_sphere(t_moving_sphere *s, t_ray *r, double t_min, double t_max, t_hit_record *rec)
{
	t_point3	cen;
	t_vec3		oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		sqrtd;
	double		root;
	t_vec3		outward_normal;

	cen = center(s, r->time);
	oc = subtract(r->origin, cen);
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
	outward_normal = divide(subtract(rec->p, cen), s->radius);
	set_face_normal(rec, r, outward_normal);

	return (TRUE);
}