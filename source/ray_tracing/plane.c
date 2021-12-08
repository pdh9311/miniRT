#include "plane.h"
#include "hit.h"

int	hit_plane(const t_ray *r, t_plane *plane, t_hit_record *rec)
{
	t_vec3	normal;
	double	check;

	normal = plane->normal;
	check = dot(r->direction, normal); 
	if (check < 1e-6)
	{
		check = dot(r->direction, plane->n_normal);
		if (check < 1e-6)
			return (FALSE);
		normal =  plane->n_normal;
	}
	rec->t = (dot(subtract(plane->point, r->origin), normal)) \
			/ check; 
	if (rec->t < TMIN || TMAX < rec->t)
		return (FALSE);
	rec->p = at(r, rec->t);
	rec->color = plane->color;
	return (TRUE);
}

t_object	plane_(t_point3 origin, t_vec3 normal, t_color albedo, t_color color)
{
	t_object	new_pl;
	t_plane		*pl;

	pl = NULL;
	new_pl.type = _plane;
	new_pl.albedo = albedo;
	new_pl.figure = malloc(sizeof(t_plane));
	pl = (t_plane *)new_pl.figure;
	if (pl)
	{
		pl->point = origin;
		pl->normal = normal;
		pl->n_normal = negate(normal);
		pl->color = color;
	}
	return (new_pl);
}