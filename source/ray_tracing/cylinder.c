/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:56:45 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:56:45 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "utils.h"

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
	if (dot(unit_vector(r->direction), rec->normal) > 0)
		rec->normal = negate(rec->normal);
	return (TRUE);
}

static int	cap_bottom(t_hit_cy *cy, const t_ray *r, \
					t_cylinder *cld, t_hit_record *rec)
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
	if (length(subtract(p, bottom)) > cld->radius)
		return (FALSE);
	rec->color = cld->color;
	rec->t = t;
	rec->p = p;
	rec->normal = cld->unit_normal;
	if (dot(unit_vector(r->direction), rec->normal) > 0)
		rec->normal = negate(rec->normal);
	return (TRUE);
}

static int	cap_top(t_hit_cy *cy, const t_ray *r, \
			t_cylinder *cld, t_hit_record *rec)
{
	float	t;
	t_vec3	p;
	float	denominator;
	t_vec3	top;

	if (dot(subtract(at(r, cy->t2), cld->point), cld->unit_normal) \
			> cld->height)
		return (FALSE);
	denominator = dot(r->direction, cld->unit_normal);
	if (denominator == 0)
		return (FALSE);
	top = add(cld->point, multiply(cld->unit_normal, cld->height));
	t = dot(cld->unit_normal, subtract(top, r->origin)) / denominator;
	p = at(r, t);
	if (length(subtract(p, top)) > cld->radius)
		return (FALSE);
	rec->color = cld->color;
	rec->t = t;
	rec->p = p;
	rec->normal = cld->unit_normal;
	if (dot(unit_vector(r->direction), rec->normal) > 0)
		rec->normal = negate(rec->normal);
	return (TRUE);
}

int	hit_cylinder(const t_ray *r, t_cylinder *cld, t_hit_record *rec)
{
	t_hit_cy	cy;

	if (eq_solve(&cy, cld, r, rec) == FALSE)
		return (FALSE);
	cy.is_between = dot(subtract(rec->p, cld->point), cld->unit_normal);
	if (cy.is_between >= 0 && cy.is_between <= cld->height && rec->t > TMIN)
		return (TRUE);
	else if (cy.is_between < 0)
	{
		if (cap_bottom(&cy, r, cld, rec) == FALSE || rec->t < TMIN)
			return (FALSE);
	}
	else
	{
		if (cap_top(&cy, r, cld, rec) == FALSE || rec->t < TMIN)
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
