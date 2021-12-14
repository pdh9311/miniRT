#ifndef CYLINDER_H
# define CYLINDER_H

# include "vec3.h"
# include "hit.h"

typedef struct s_cylinder
{
	t_point3	point;
	t_vec3		normal;
	t_vec3		unit_normal;
	double		radius;
	double		height;
	t_color		color;
}				t_cylinder;

typedef struct s_hit_cy
{
	double	a;
	double	half_b;
	double	c;
	double	discrimiant;
	t_vec3	w;
	double	is_between;
	double	tmp;	// ray가 원통의 평면과 교차할때의 t값	
	t_vec3	normal;
	double	check;
}				t_hit_cy;

int			hit_cylinder(const t_ray *r, t_cylinder *cylinder, t_hit_record *rec);
t_object	cylinder_(t_point3 origin, t_vec3 normal, t_color albedo, t_color color, double radius, double height);

#endif