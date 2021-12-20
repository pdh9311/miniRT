#ifndef CYLINDER_H
# define CYLINDER_H

# include "vec3.h"
# include "hit.h"

typedef struct s_cylinder
{
	t_point3	point;
	t_vec3		normal;
	t_vec3		unit_normal;
	float		radius;
	float		height;
	t_color		color;
	t_color		albedo;
}				t_cylinder;

typedef t_cylinder	t_cy_info;
typedef t_cylinder	t_cone;
/**
 * tmp : ray가 원통의 평면과 교차할때의 t값
 */
typedef struct s_hit_cy
{
	float	a;
	float	half_b;
	float	c;
	float	discrimiant;
	t_vec3	w;
	float	t1;
	float	t2;
	float	is_between;
	float	tmp;
	t_vec3	normal;
}				t_hit_cy;

int			hit_cylinder(const t_ray *r, \
				t_cylinder *cylinder, t_hit_record *rec);
t_object	cylinder_(t_cy_info cy_info);
#endif
