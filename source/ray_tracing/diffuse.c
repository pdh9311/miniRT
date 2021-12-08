#include "miniRT.h"

void	set_diffuse(t_color *pixel_color, t_scene *scene, t_hit_record *rec, t_phong *phong)
{
	phong->light_dir = subtract(scene->light.origin, rec->p);
	phong->light_unit_dir = unit_vector(phong->light_dir);
	phong->kd = fmax(dot(rec->normal, phong->light_unit_dir), 0.0);
	multiply_(pixel_color, phong->kd);
}