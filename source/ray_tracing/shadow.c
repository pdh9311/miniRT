#include "miniRT.h"

/*
static int	hit_cylinder1(const t_ray *r, t_cylinder *cylinder, t_hit_record *rec)
{
	double	a;
	double	b;
	double	c;
	double	discrimiant;
	t_vec3	w;
	double	is_between;
	double	tmp;

	w = subtract(r->origin, cylinder->point);
	a = dot(r->direction, r->direction) - pow(dot(r->direction, cylinder->unit_normal), 2);
	b = dot(r->direction, w) - (dot(r->direction, cylinder->unit_normal) * dot(w, cylinder->unit_normal));
	c = dot(w, w) - pow(dot(w, cylinder->unit_normal), 2) - pow(cylinder->radius, 2);
	discrimiant = pow(b, 2) - (a * c);

	rec->color = cylinder->color;
	if (discrimiant < 0)
		return (FALSE);
	rec->t = (-b - sqrt(discrimiant)) / a;
		//printf("t1: %lf\n", rec->t);
	if (rec->t < TMIN || TMAX < rec->t)
	{
		//rec->t = (-b + sqrt(discrimiant)) / a;
		//if (rec->t < TMIN || TMAX < rec->t)
			return (FALSE);
	}
		//printf("t2: %lf\n", rec->t);
	rec->p = at(r, rec->t);
	rec->normal = unit_vector(subtract(rec->p, multiply(cylinder->unit_normal, dot(subtract(rec->p, cylinder->point), cylinder->unit_normal))));
	is_between = dot(subtract(rec->p, cylinder->point), cylinder->unit_normal);
	if (is_between >= 0 && is_between <= cylinder->height)	// 첫 교차점이 cylinder 곡면이면
		return (TRUE);
	else if (is_between < 0)	// 첫 교차점이 cylinder 바닥면이면
	{
		tmp = (dot(subtract(cylinder->point, r->origin), cylinder->unit_normal)) / (dot(r->direction, cylinder->unit_normal));
		if (tmp < (-b + sqrt(discrimiant)) / a)
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
		if (tmp < (-b + sqrt(discrimiant)) / a)
			rec->t = tmp;
		rec->p = at(r, rec->t);
		rec->normal = cylinder->unit_normal;
		if (length(subtract(rec->p, add(cylinder->point, multiply(cylinder->unit_normal, cylinder->height)))) <= cylinder->radius)
			return (TRUE);
		return (FALSE);
	}
	return (TRUE);
}

static int	hit_sphere1(const t_ray *r, t_sphere *sphere, t_hit_record *rec)
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
	printf("t1: %lf\n", rec->t);
	if (rec->t < TMIN || TMAX < rec->t)
	{
		rec->t = (-half_b + sqrt(discrimiant)) / a;
		if (rec->t < TMIN || TMAX < rec->t)
			return (FALSE);
	}
	printf("t2: %lf\n", rec->t);
	rec->p = at(r, rec->t);
	rec->normal = unit_vector(subtract(rec->p, sphere->center));
	if (dot(r->direction, rec->normal) > 0)
		rec->normal = negate(rec->normal);
	rec->color = sphere->color;
	return (TRUE);	 
}

static int	hit_1(t_object *object, t_ray *r, t_hit_record *rec)
{
	int	is_hit;

	is_hit = FALSE;
	if (object->type != _none)
	{
		if (object->type == _sphere)
			is_hit = hit_sphere1(r, object->figure, rec);
		else if (object->type == _plane)
			is_hit = hit_plane(r, object->figure, rec);
		else if (object->type == _cylinder)
			is_hit = hit_cylinder1(r, object->figure, rec);
	}
	if (is_hit)
		rec->albedo = object->albedo;
	return (is_hit);
}

int	hit1(t_hlist *current, t_ray *r, t_hit_record *rec, double max)
{
	t_hit_record	temp_rec;
	double			closest_so_far;
	int				hit_anything;
	
	hit_anything = FALSE;
	closest_so_far = max;
	while (current)
	{
		if (hit_1(&current->object, r, &temp_rec))	// p, normal, t
		{
			if (temp_rec.t < closest_so_far)
			{
				hit_anything = TRUE;
				closest_so_far = temp_rec.t; 
				*rec = temp_rec;
			}
		}
		current = current->next;
	}
	return (hit_anything);
}
*/

int	set_shadow(t_scene *scene, t_hit_record *rec, t_phong *phong)
{
	phong->light_len = length(phong->light_dir);
	phong->light_ray = ray_(rec->p, phong->light_unit_dir);
	if (hit(scene->list, &phong->light_ray, &phong->shadow_rec, phong->light_len))
		return (TRUE);
	return (FALSE);
}