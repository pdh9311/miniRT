#include "cylinder.h"
#include "utils.h"

int	eq_solve(t_hit_cy *cy, t_cylinder *cld, \
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
	cy->t1 = (-(cy->half_b) - sqrt(cy->discrimiant)) / cy->a;
	cy->t2 = (-(cy->half_b) + sqrt(cy->discrimiant)) / cy->a;
	rec->color = cld->color;
	if (cy->discrimiant < 0)
		return (FALSE);
	rec->t = cy->t1;
	rec->p = at(r, rec->t);
	rec->normal = unit_vector(subtract(subtract(rec->p, cld->point), \
		multiply(cld->unit_normal, \
		dot(subtract(rec->p, cld->point), cld->unit_normal))));
	return (TRUE);
}
/*
int	check_cy_p(t_cylinder *cld, t_hit_record *rec)
{
	t_point3	bottom;
	t_point3	top;
	t_vec3		bottom_p;
	t_vec3		top_p;

	bottom = cld->point;
	top = add(cld->point, multiply(cld->unit_normal, cld->height));
	bottom_p = subtract(rec->p, bottom);
	top_p = subtract(rec->p, top);
	if (dot(cld->unit_normal, bottom_p) < 0)	// 다른 방향이면
		return (FALSE);
	if (dot(cld->unit_normal, top_p) > 0)	// 같은 방향이면
		return (FALSE);
	if (rec->t <= 0 || rec->t > TMAX)
		return (FALSE);
	return (TRUE);
}

int	check_cap_range(const t_ray *r, t_cylinder *cld, double t, t_vec3 cap_center)
{
	t_vec3	tmp;

	tmp = subtract(at(r, t), subtract(cap_center, r->origin));
	if (length(tmp) > cld->radius)
		return (FALSE);
	else
		return (TRUE);
}


float	cap_solve_t(const t_ray *r, t_cylinder *cld)
{
	t_vec3	bottom;
	t_vec3	top;
	float	denominator;
	double	bottom_t;
	double	top_t;

	denominator = dot(r->direction, cld->unit_normal);
	if (denominator == 0)
		return (TMAX);
	bottom = cld->point;
	bottom_t = dot(cld->unit_normal, subtract(bottom, r->origin)) / denominator;
	if (check_cap_range(r, cld, bottom_t, bottom) == FALSE)
		bottom_t = TMAX;
	top = add(cld->point, multiply(cld->unit_normal, cld->height));
	top_t = dot(cld->unit_normal, subtract(top, r->origin)) / denominator;
	if (check_cap_range(r, cld, top_t, top) == FALSE)
		top_t = TMAX;
	if (top_t < TMIN || top_t >TMAX)
		top_t = TMAX;
	if (bottom_t < TMIN || bottom_t >TMAX)
		bottom_t = TMAX;
	if (top_t < bottom_t)
		return (top_t);
	else
		return (bottom_t);
}
*/

int	check_cap_range(t_vec3 p, t_vec3 cap_center, float radius)
{
	t_vec3	tmp;

	tmp = subtract(p, cap_center);
	if (length(tmp) > radius)
		return (FALSE);
	else
		return (TRUE);
}

int	cap_bottom(t_hit_cy *cy, const t_ray *r, t_cylinder *cld, t_hit_record *rec)
{
	float	t;
	t_vec3	p;
	float	denominator;
	t_vec3	bottom;

	if (dot(subtract(at(r, cy->t2), cld->point), cld->unit_normal) < 0)
		return (FALSE);
	denominator = dot(r->direction, cld->unit_normal);
	if (denominator == 0)
		return (FALSE);
	bottom = cld->point;
	t = dot(cld->unit_normal, subtract(bottom, r->origin)) / denominator;
	p = at(r, t);
	if (check_cap_range(p, bottom, cld->radius) == FALSE)
		return (FALSE);
	rec->t = t;
	rec->p = p;
	rec->normal = cld->unit_normal;
	if (dot(unit_vector(r->direction), rec->normal) < 0)
		rec->normal = negate(rec->normal);
	return (TRUE);
}

int	cap_top(t_hit_cy *cy, const t_ray *r, t_cylinder *cld, t_hit_record *rec)
{
	float	t;
	t_vec3	p;
	float	denominator;
	t_vec3	top;

	if (dot(subtract(at(r, cy->t2), cld->point), cld->unit_normal) > cld->height)
		return (FALSE);
	denominator = dot(r->direction, cld->unit_normal);
	if (denominator == 0)
		return (FALSE);
	top = add(cld->point, multiply(cld->unit_normal, cld->height));
	t = dot(cld->unit_normal, subtract(top, r->origin)) / denominator;
	p = at(r, t);
	if (check_cap_range(p, top, cld->radius) == FALSE)
		return (FALSE);
	rec->t = t;
	rec->p = p;
	rec->normal = cld->unit_normal;
	if (dot(unit_vector(r->direction), rec->normal) < 0)
		rec->normal = negate(rec->normal);
	return (TRUE);
}

int	hit_cylinder(const t_ray *r, t_cylinder *cld, t_hit_record *rec)
{
	t_hit_cy	cy;
	float		cap_t;

	if (eq_solve(&cy, cld, r, rec) == FALSE)	// t, p, normal 구하기.
		return (FALSE);
	cy.is_between = dot(subtract(rec->p, cld->point), cld->unit_normal);
	if (cy.is_between >= 0 && cy.is_between <= cld->height)
		return (TRUE);
	else if (cy.is_between < 0)
	{
		if (cap_bottom(&cy, r, cld, rec) == FALSE)
			return (FALSE);
	}
	else
	{
		if (cap_top(&cy, r, cld, rec) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

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
		cy->point = cy_info.point;
		cy->normal = cy_info.normal;
		cy->unit_normal = unit_vector(cy->normal);
		cy->color = cy_info.color;
		cy->radius = cy_info.radius;
		cy->height = cy_info.height;
	}
	return (new_cy);
}
