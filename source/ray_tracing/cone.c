#include "cone.h"

static int	co_eq_solve(t_hit_co *co, t_cone *cone, \
				const t_ray *r, t_hit_record *rec)
{
	co->bottom = cone->point;
	co->top = add(co->bottom, multiply(cone->unit_normal, cone->height));
	co->m = pow(cone->radius, 2) / pow(cone->height, 2);

	co->w = subtract(co->top, r->origin);
	co->a = dot(r->direction, r->direction) - (1 + co->m) * pow(dot(r->direction, cone->unit_normal), 2);
	co->half_b = (1 + co->m) * dot(co->w, cone->unit_normal) * dot(r->direction, cone->unit_normal) - dot(co->w, r->direction);
	co->c = dot(co->w, co->w) - (1 + co->m) * pow(dot(co->w, cone->unit_normal), 2);
	co->discrimiant = pow(co->half_b, 2) - (co->a * co->c);
	if (co->discrimiant < 0)
		return (FALSE);
	co->t1 = (-co->half_b - sqrt(co->discrimiant)) / co->a;
	co->t2 = (-co->half_b + sqrt(co->discrimiant)) / co->a;
	rec->t = co->t1;
	rec->p = at(r, rec->t);
	co->q = multiply(cone->unit_normal, dot(subtract(rec->p, co->bottom), cone->unit_normal));
	rec->normal = cross(cross(subtract(co->top, co->q), subtract(rec->p, co->q)), subtract(co->top, rec->p));
	rec->color = cone->color;
	return (TRUE);
}
/*
static int	co_eq_solve(t_hit_co *co, t_cone *cone, \
				const t_ray *r, t_hit_record *rec)
{
	co->bottom = cone->point;
	co->top = add(co->bottom, multiply(cone->unit_normal, cone->height));
	co->m = pow(cone->radius, 2) / pow(cone->height, 2);

	co->w = subtract(r->origin, co->top);
	co->a = dot(r->direction, r->direction) - (1 + co->m) * pow(dot(r->direction, cone->unit_normal), 2);
	// co->half_b = (1 + co->m) * dot(co->w, cone->unit_normal) * dot(r->direction, cone->unit_normal) - dot(co->w, r->direction);
	co->half_b = dot(co->w, r->direction) - (1 + co->m) * dot(r->direction, cone->unit_normal) * dot(co->w, cone->unit_normal);
	co->c = dot(co->w, co->w) - (1 + co->m) * pow(dot(co->w, cone->unit_normal), 2);
	co->discrimiant = pow(co->half_b, 2) - (co->a * co->c);
	if (co->discrimiant < 0)
		return (FALSE);
	co->t1 = (-co->half_b - sqrt(co->discrimiant)) / co->a;
	co->t2 = (-co->half_b + sqrt(co->discrimiant)) / co->a;
	rec->t = co->t1;
	rec->p = at(r, rec->t);

	co->q = multiply(cone->unit_normal, dot(subtract(rec->p, co->bottom), cone->unit_normal));

	rec->normal = cross(cross(subtract(co->top, co->q), subtract(rec->p, co->q)), subtract(co->top, rec->p));
	rec->color = cone->color;
	return (TRUE);
}
*/
/*
 int	bottom_plane(const t_ray *r, t_hit_co *co, t_cone *cone, t_hit_record *rec)
{
	float	t;
	t_vec3	p;
	float	denominator;
	t_vec3	bottom;

	if (dot(subtract(at(r, co->t2), cone->point), cone->unit_normal) < 0)
		return (FALSE);
	denominator = dot(r->direction, cone->unit_normal);
	if (denominator == 0)
		return (FALSE);
	bottom = cone->point;
	t = dot(cone->unit_normal, subtract(bottom, r->origin)) / denominator;
	p = at(r, t);
	if (length(subtract(p, bottom)) > cone->radius)
		return (FALSE);
	// rec->color = cone->color;
	rec->t = t;
	rec->p = p;
	rec->normal = cone->unit_normal;
	return (TRUE);
}
*/
int	hit_cone(const t_ray *r, t_cone *cone, t_hit_record *rec)
{
	t_hit_co	co;
	// float		is_between;

	if (co_eq_solve(&co, cone, r, rec) == FALSE)
		return (FALSE);
	// is_between = dot(subtract(rec->p, cone->point), cone->unit_normal);
	// if (is_between >= 0 && is_between <= cone->height)
	// 	return (TRUE);
	// else if (is_between < 0)
	// {
	// 	// bottom_plane(r, &co, cone, rec);
	// }
	// else
	// 	return (FALSE);
	return (TRUE);
}

t_object	cone_(t_cy_info cone_info)
{
	t_object	new_co;
	t_cone		*cone;

	cone = NULL;
	new_co.type = _cone;
	new_co.albedo = cone_info.albedo;
	new_co.figure = malloc(sizeof(t_cylinder));
	cone = (t_cylinder *)new_co.figure;
	if (cone)
	{
		cone->point = cone_info.point;
		cone->normal = cone_info.normal;
		cone->unit_normal = unit_vector(cone->normal);
		cone->color = cone_info.color;
		cone->radius = cone_info.radius;
		cone->height = cone_info.height;
	}
	return (new_co);
}
