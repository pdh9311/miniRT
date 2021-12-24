#ifndef CONE_H
# define CONE_H

#include "cylinder.h"

typedef struct s_hit_co
{
	t_vec3	bottom;
	t_vec3	top;
	float	m;

	t_vec3	w;
	float	a;
	float	half_b;
	float	c;
	float	discrimiant;
	float	t1;
	float	t2;
	t_vec3	q;
}				t_hit_co;

int			hit_cone(const t_ray *r, t_cone *cone, t_hit_record *rec);
t_object	cone_(t_cy_info cone_info);

#endif
