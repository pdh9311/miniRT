#include "miniRT.h"

int	set_shadow(t_scene *scene, t_hit_record *rec, t_phong *phong)
{
	phong->light_len = length(phong->light_dir);
	phong->light_ray = ray_(rec->p, phong->light_unit_dir);
	if (hit(scene->list, &phong->light_ray, &phong->shadow_rec, phong->light_len))
		return (TRUE);
	return (FALSE);
}