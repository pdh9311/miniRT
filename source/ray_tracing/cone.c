#include "cone.h"

typedef struct s_hit_co
{
	t_vec3	bottom;
	t_vec3	top;
	double	m;

	t_vec3	w;
	double	a;
	double	half_b;
	double	c;
	double	discrimiant;
	double	t1;
	double	t2;
	double	t;
	t_vec3	p;
	t_vec3	normal;
	t_vec3	q;

}				t_hit_co;

int	co_eq_solve(t_hit_co *co, t_cone *cone, \
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
	co->t1 = (-co->half_b -sqrt(co->discrimiant)) / co->a;
	co->t2 = (-co->half_b +sqrt(co->discrimiant)) / co->a;
	co->t = co->t1;
	co->p = at(r, co->t);
	co->q = multiply(cone->unit_normal, dot(co->p, cone->unit_normal));
	co->normal = cross(cross(subtract(co->top, co->q), subtract(co->p, co->q)), subtract(co->top, co->p));
	return (TRUE);
}

int	hit_cone(const t_ray *r, t_cone *cone, t_hit_record *rec)
{
	t_hit_co	co;
	if (co_eq_solve(&co, cone, r, rec) == FALSE)
		return (FALSE);
	// double	is_between;
	// is_between = dot()

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
