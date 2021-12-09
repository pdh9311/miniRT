#include "miniRT.h"

void	set_diffuse(t_color *pixel_color, t_scene *scene, t_hit_record *rec, t_phong *phong)
{
	// printf("%lf %lf %lf\n", rec->color.x, rec->color.y, rec->color.z);
	phong->light_dir = subtract(scene->light.origin, rec->p);
	phong->light_unit_dir = unit_vector(phong->light_dir);
	phong->kd = fmax(dot(rec->normal, phong->light_unit_dir), 0.0);
	// printf("%lf %lf %lf\n", rec->normal.x, rec->normal.y, rec->normal.z);
	// printf("%lf %lf %lf\n", phong->light_dir.x, phong->light_dir.y, phong->light_dir.z);
	// printf("%lf\n\n", phong->kd);
	multiply_(pixel_color, phong->kd);
}