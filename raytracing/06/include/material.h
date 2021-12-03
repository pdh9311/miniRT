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
	t_color		albedo;
	t_surface	surface;
	double		fuzz;
	double		ir;
}	t_material;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	t_material	material;
	double		t;
	int			front_face;
}	t_hit_record;

t_material	material_(t_surface s, t_color c, double f, double ir);
double		reflectance(double cosine, double ref_idx);
int			scatter(t_ray *r_in, t_hit_record *rec, t_color *attenuation, t_ray *scattered);
#endif
