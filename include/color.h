#ifndef COLOR_H
# define COLOR_H

# include "vec3.h"
# include "rtweekend.h"
# include "miniRT.h"

//void write_color(t_color pixel_color, int samples_per_pixel);
void	write_color(t_mlx *mlx, t_color pixel_color, int j, int i, int width);

#endif