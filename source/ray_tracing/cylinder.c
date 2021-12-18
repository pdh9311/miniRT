#include "cylinder.h"

static int	cy_plane(t_hit_cy *cy, t_cylinder *cld, \
			const t_ray *r, t_hit_record *rec)
{
	t_vec3	normal;
	float	check;

	normal = cld->unit_normal;
	check = dot(r->direction, normal);
	if (check < 1e-6)
	{
		check = dot(r->direction, negate(cld->unit_normal));
		if (check < 1e-10)
			return (FALSE);
		normal = negate(cld->unit_normal);
	}
	cy->tmp = (dot(subtract(cld->point, r->origin), normal)) \
		/ check;
	if (cy->tmp < TMIN || TMAX < cy->tmp)
		return (FALSE);
	if (cy->tmp < (-(cy->half_b) + sqrt(cy->discrimiant)) / cy->a)
		rec->t = cy->tmp;
	rec->p = at(r, cy->tmp);
	rec->normal = normal;
	return (TRUE);
}

static int	eq_solve(t_hit_cy *cy, t_cylinder *cld, \
				const t_ray *r, t_hit_record *rec)
{
	cy->w = subtract(r->origin, cld->point);
	cy->a = dot(r->direction, r->direction) \
		- pow(dot(r->direction, cld->unit_normal), 2);
	cy->half_b = dot(r->direction, cy->w) \
		- (dot(r->direction, \
			cld->unit_normal) * dot(cy->w, cld->unit_normal));
	cy->c = dot(cy->w, cy->w) - pow(dot(cy->w, cld->unit_normal), 2) \
			- pow(cld->radius, 2);
	cy->discrimiant = pow(cy->half_b, 2) - (cy->a * cy->c);
	rec->color = cld->color;
	if (cy->discrimiant < 0)
		return (FALSE);
	rec->t = (-(cy->half_b) - sqrt(cy->discrimiant)) / cy->a;
	if (rec->t < TMIN || TMAX < rec->t)
	{
		rec->t = (-(cy->half_b) + sqrt(cy->discrimiant)) / cy->a;
		if (rec->t < TMIN || TMAX < rec->t)
			return (FALSE);
	}
	rec->p = at(r, rec->t);
	rec->normal = unit_vector(subtract(subtract(rec->p, cld->point), \
		multiply(cld->unit_normal, \
		dot(subtract(rec->p, cld->point), cld->unit_normal))));
	return (TRUE);
}

int	hit_cylinder(const t_ray *r, t_cylinder *cld, t_hit_record *rec)
{
	t_hit_cy	cy;

	if (!eq_solve(&cy, cld, r, rec))
		return (FALSE);
	cy.is_between = dot(subtract(rec->p, cld->point), cld->unit_normal);
	if (cy.is_between >= 0 && cy.is_between <= cld->height)
		return (TRUE);
	else if (cy.is_between < 0)
	{
		if (!cy_plane(&cy, cld, r, rec))
			return (FALSE);
		if (length(subtract(rec->p, cld->point)) <= cld->radius)
			return (TRUE);
		return (FALSE);
	}
	else
	{
		if (!cy_plane(&cy, cld, r, rec))
			return (FALSE);
		if (length(subtract(rec->p, add(cld->point, \
		multiply(cld->unit_normal, cld->height)))) <= cld->radius)
			return (TRUE);
		return (FALSE);
	}
	return (TRUE);
}

// t_object	cylinder_(t_point3 origin, t_vec3 normal, t_color albedo, \
// 				t_color color, float radius, float height)
t_object	cylinder_(t_cy_info cy_info)
{
	t_object	new_cy;
	t_cylinder	*cy;

	cy = NULL;
	new_cy.type = _cylinder;
	new_cy.albedo = cy_info.albedo;
	new_cy.figure = malloc(sizeof(t_cylinder));
	cy = (t_cylinder *)new_cy.figure;
	if (cy)
	{
		cy->point = cy_info.origin;
		cy->normal = cy_info.normal;
		cy->unit_normal = unit_vector(cy->normal);
		cy->color = cy_info.color;
		cy->radius = cy_info.radius;
		cy->height = cy_info.height;
	}
	return (new_cy);
}
