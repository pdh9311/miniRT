#include "cylinder.h"

int	hit_cylinder(const t_ray *r, t_cylinder *cylinder, t_hit_record *rec)
{
	double	a;
	double	half_b;
	double	c;
	double	discrimiant;
	t_vec3	w;
	double	is_between;
	double	tmp;	// ray가 원통의 평면과 교차할때의 t값

	w = subtract(r->origin, cylinder->point);
	a = dot(r->direction, r->direction) - pow(dot(r->direction, cylinder->unit_normal), 2);
	half_b = dot(r->direction, w) - (dot(r->direction, cylinder->unit_normal) * dot(w, cylinder->unit_normal));
	c = dot(w, w) - pow(dot(w, cylinder->unit_normal), 2) - pow(cylinder->radius, 2);
	discrimiant = pow(half_b, 2) - (a * c);
	rec->color = cylinder->color;
	if (discrimiant < 0)
		return (FALSE);
	rec->t = (-half_b - sqrt(discrimiant)) / a;
	if (rec->t < TMIN || TMAX < rec->t)
	{
		rec->t = (-half_b + sqrt(discrimiant)) / a;
		if (rec->t < TMIN || TMAX < rec->t)
			return (FALSE);
	}
	rec->p = at(r, rec->t);
	rec->normal = unit_vector(
		subtract(
			subtract(rec->p, cylinder->point),
					multiply(cylinder->unit_normal, dot(subtract(rec->p, cylinder->point), cylinder->unit_normal))
		)
	);
	is_between = dot(subtract(rec->p, cylinder->point), cylinder->unit_normal);
	if (is_between >= 0 && is_between <= cylinder->height)	// 첫 교차점이 cylinder 곡면이면
		return (TRUE);
	else if (is_between < 0)	// 첫 교차점이 cylinder 바닥면이면
	{
		tmp = (dot(subtract(cylinder->point, r->origin), cylinder->unit_normal)) / (dot(r->direction, cylinder->unit_normal));
		if (tmp < (-half_b + sqrt(discrimiant)) / a)
			rec->t = tmp;
		rec->p = at(r, rec->t);
		rec->normal = negate(cylinder->unit_normal);
		if (length(subtract(rec->p, cylinder->point)) <= cylinder->radius)
			return (TRUE);
		return (FALSE);
	}
	else	// 첫 교차점이 cylinder 윗면이면
	{
		tmp = (dot(subtract(cylinder->point, r->origin), cylinder->unit_normal)) / (dot(r->direction, cylinder->unit_normal));
		if (tmp < (-half_b + sqrt(discrimiant)) / a)
			rec->t = tmp;
		rec->p = at(r, rec->t);
		rec->normal = cylinder->unit_normal;
		if (length(subtract(rec->p, add(cylinder->point, multiply(cylinder->unit_normal, cylinder->height)))) <= cylinder->radius)
			return (TRUE);
		return (FALSE);
	}
	return (TRUE);
}

t_object	cylinder_(t_point3 origin, t_vec3 normal, t_color albedo, t_color color, double radius, double height)
{
	t_object	new_cy;
	t_cylinder	*cy;

	cy = NULL;
	new_cy.type = _cylinder;
	new_cy.albedo = albedo;
	new_cy.figure = malloc(sizeof(t_cylinder));
	cy = (t_cylinder *)new_cy.figure;
	if (cy)
	{
		cy->point = origin;
		cy->normal = normal;
		cy->unit_normal = unit_vector(cy->normal);
		cy->color = color;
		cy->radius = radius;
		cy->height = height;
	}
	return (new_cy);
}
