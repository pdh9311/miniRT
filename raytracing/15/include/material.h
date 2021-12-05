#ifndef MATERIAL_H
# define MATERIAL_H

# include "rtweekend.h"
# include "vec3.h"
# include "ray.h"

typedef enum e_surface
{
	metal,
	lambertian,
	dielectric
}	t_surface;

typedef struct s_material
{
	t_color		albedo;		// 천제 표면의 반사율. 표면의 상태, 물질의 종류를 추정하는 실마리를 제공
	t_surface	surface;
	double		fuzz;
	double		ir;
}	t_material;

typedef struct s_hit_record
{
	t_point3	p;			// 물체와 부딪힌 지점
	t_vec3		normal;
	t_material	material;
	double		t;
	int			front_face;	// 물체 안에 있는지 밖에 있는지 판단하는 변수
}	t_hit_record;

t_material	material_(t_surface s, t_color c, double f, double ir);
int			scatter(t_ray r_in, t_hit_record *rec, t_color *attenuation, t_ray *scattered);

#endif
