#include "miniRT.h"

void	set_ambient(t_color *pixel_color, t_scene *scene, t_hit_record *rec)
{
	*pixel_color = multiply__(*pixel_color, rec->albedo);
	add_(pixel_color, scene->ambient.color);
	multiply_(pixel_color, scene->ambient.bright_ratio);
	vec_min(pixel_color, (t_color){1.0, 1.0, 1.0});
}