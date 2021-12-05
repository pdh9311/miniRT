#include "color.h"
#include "rtweekend.h"

void	input_color(t_data *data, t_color pixel_color, int samples_per_pixel)
{
	double	scale = 1.0 / samples_per_pixel;
	double	r = pixel_color.x * scale;
	double	g = pixel_color.y * scale;
	double	b = pixel_color.z * scale;

	data->rgb[0] = 255. * clamp(r, 0.0, 0.999);
	data->rgb[1] = 255. * clamp(g, 0.0, 0.999);
	data->rgb[2] = 255. * clamp(b, 0.0, 0.999);
	data->color = data->rgb[0] << 16 | data->rgb[1] << 8 | data->rgb[2];
}
