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

int			hit_cylinder(const t_ray *r, t_cylinder *cylinder, t_hit_record *rec);
t_object	cylinder_(t_point3 origin, t_vec3 normal, t_color albedo, t_color color, double radius, double height);

#endif