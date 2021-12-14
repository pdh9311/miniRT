#ifndef SPHERE_H
# define SPHERE_H

# include "vec3.h"
# include "ray.h"
# include "hit.h"

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	t_color		color;
}				t_sphere;

typedef struct s_hit_sphere
{
	t_vec3		oc;
	double		a;
	double		half_b;
	double		c;
	double		discrimiant;
}				t_hit_sphere;

int			hit_sphere(const t_ray *r, t_sphere *sphere, t_hit_record *rec);
t_object	sphere_(t_point3 center, double radius, t_color albedo, t_color color);

#endif