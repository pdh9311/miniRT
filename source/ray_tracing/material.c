#include "material.h"

t_material	material_(t_surface s, t_color c, double f, double ir)
{
	t_material	m;

	m.surface = s;
	m.albedo = c;
	m.fuzz = f;
	m.ir = ir;
	return (m);
}

static double reflectance(double cosine, double ref_idx)
{
	double r0;

	r0 = (1-ref_idx) / (1+ref_idx);
	r0 = r0*r0;
	return (r0 + (1-r0)*pow((1-cosine), 5));
}

int scatter(t_ray *r_in, t_hit_record *rec, t_color *attenuation, t_ray *scattered)
{
	t_vec3 direction;
	t_vec3 unit_direction;
	double refraction_ratio;
	double cos_theta; 
	double sin_theta; 

	switch (rec->material.surface)
	{
		case lambertian:
			direction = add(rec->normal, random_unit_vector());

			if (near_zero(direction))
				direction = rec->normal;
			break;
		case dielectric:
			refraction_ratio = rec->front_face ? (1.0/rec->material.ir) : rec->material.ir;

			unit_direction = unit_vector(r_in->direction);
			cos_theta = fmin(dot(negate(unit_direction), rec->normal), 1.0);
			sin_theta = sqrt(1.0 - cos_theta*cos_theta);

			if (refraction_ratio * sin_theta > 1.0 || reflectance(cos_theta, refraction_ratio) > random_double())
				direction = reflect(unit_vector(r_in->direction), rec->normal);
			else
				direction = refract(unit_direction, rec->normal, refraction_ratio);
				break;
		case metal:
			direction = reflect(unit_vector(r_in->direction), rec->normal);
				add_(&direction, multiply(random_in_unit_sphere(), rec->material.fuzz));
			break;
	}
	*scattered = ray_(rec->p, direction, r_in->time);
	*attenuation = rec->material.albedo;

	return (rec->material.surface != metal || dot(scattered->direction, rec->normal) > 0);
}

/*
int scatter(t_ray *r_in, t_hit_record *rec, t_color *attenuation, t_ray *scattered)
{
	t_vec3 direction;
	t_vec3 unit_direction;
	double refraction_ratio;
	double cos_theta; 
	double sin_theta; 

	if (rec->material.surface == lambertian)
		// do lambertian
		;
	else if (rec->material.surface == dielectric)
		// do dielectric
		;
	else if (rec->material.surface == metal)
		// do metal
		;
	*scattered = ray_(rec->p, direction, r_in->time);
	*attenuation = rec->material.albedo;

	return (rec->material.surface != metal || dot(scattered->direction, rec->normal) > 0);
}
*/