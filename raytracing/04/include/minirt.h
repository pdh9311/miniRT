#ifndef MINIRT_H
# define MINIRT_H

#include "mlx.h"
#include "vec3.h"

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	int		rgb[3];
	int		color;

	double		aspect_ratio;
	int			img_height;
	int			img_width;

	int			win_height;
	int			win_width;

	double		viewport_height;
	double		viewport_width;
	int			facal_length;

	t_point3	origin;
	t_vec3		horizontal;	// fix
	t_vec3		vertical;		// fix
	t_vec3		focal;
	t_vec3		lower_left_corner;

	double		alpha;
	double		beta;
	double		gamma;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
