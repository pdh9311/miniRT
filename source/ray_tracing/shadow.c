#include "miniRT.h"

int	set_shadow(t_scene *scene, t_hit_record *rec, t_phong *phong)
{
	phong->light_len = length(phong->light_dir);
	// phong->light_ray = ray_(rec->p, phong->light_unit_dir);
	phong->light_ray = ray_(add(rec->p, multiply(rec->normal, 1e-6)), phong->light_unit_dir);
	// printf("%f %f %f\n", phong->light_unit_dir.x, phong->light_unit_dir.y, phong->light_unit_dir.z);
	// phong->light_ray = ray_(add(rec->p, rec->normal), phong->light_unit_dir);
	// printf("%f %f %f\n", phong->light_ray.direction.x, phong->light_ray.direction.y, phong->light_ray.direction.z);
	if (hit(scene->list, &phong->light_ray, \
			&phong->shadow_rec, phong->light_len))
	{
	// printf("=---=====\n");
	// printf("%f %f %f\n", rec->p.x, rec->p.y, rec->p.z);
	// 	printf("%f %f %f\n", phong->shadow_rec.p.x, phong->shadow_rec.p.y, phong->shadow_rec.p.z);
		return (TRUE);
	}
	return (FALSE);
}
