#include "miniRT.h"

void	set_specular(t_color *pixel_color, t_scene *scene, t_hit_record *rec, t_phong *phong)
{
	phong->ksn = 128;	// shininess value
	phong->ks = 0.5;	// phong->specular strength

	phong->view_dir = unit_vector(negate(scene->ray.direction));
	phong->reflect_dir = reflect(phong->light_unit_dir, rec->normal);
	phong->spec = pow(fmax(dot(phong->view_dir, phong->reflect_dir), 0.0), phong->ksn);
	phong->specular = multiply(*pixel_color, phong->ks * phong->spec);
	add_(pixel_color, phong->specular);
	vec_min(pixel_color, (t_color){1.0, 1.0, 1.0});
}
