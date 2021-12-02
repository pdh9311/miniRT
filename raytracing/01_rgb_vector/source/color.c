#include "color.h"

void	input_color(t_data *data, t_color pixel_color)
{
		data->rgb[0] = 255. * pixel_color.x;
		data->rgb[1] = 255. * pixel_color.y;
		data->rgb[2] = 255. * pixel_color.z;
		data->color = data->rgb[0] << 16 | data->rgb[1] << 8 | data->rgb[2];
}
