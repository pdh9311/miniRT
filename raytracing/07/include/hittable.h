#ifndef HITTABLE_H
# define HITTABLE_H

# include "rtweekend.h"
# include "ray.h"
# include "vec3.h"

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		t;
	int			front_face;	// 물체 안에 있는지 밖에 있는지 판단하는 변수
}	t_hit_record;

void	set_face_normal(t_hit_record *rec, t_ray r, t_vec3 outward_normal);
#endif
