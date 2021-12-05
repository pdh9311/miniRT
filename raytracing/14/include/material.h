#ifndef MATERIAL_H
# define MATERIAL_H

# include "rtweekend.h"
# include "vec3.h"
# include "ray.h"

typedef struct s_hit_record
{
	t_point3	p;			// 물체와 부딪힌 지점
	t_vec3		normal;
	double		t;
	int			front_face;	// 물체 안에 있는지 밖에 있는지 판단하는 변수
}	t_hit_record;

#endif
