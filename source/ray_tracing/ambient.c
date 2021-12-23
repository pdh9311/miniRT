#include "miniRT.h"

void	set_ambient(t_color *pixel_color, t_scene *scene, t_hit_record *rec)
{
	t_color		ambient;

	ambient = multiply(scene->ambient.color, scene->ambient.bright_ratio);
	add_(pixel_color, ambient);
	*pixel_color = multiply__(*pixel_color, rec->color);
	vec_min(pixel_color, (t_color){1.0, 1.0, 1.0});
}
