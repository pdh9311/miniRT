#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include "camera.h"
# include "ray.h"

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*data;
	int			bpp;
	int			size_l;
	int			endian;
	int			color[3];
}				t_mlx;

typedef struct s_scene
{
	t_mlx		mlx;
	t_camera	camera;
}				t_scene;

double	degrees_to_radians(double degrees);
double	random_double(void);
double	random_double_(double min, double max);
double	clamp(double x, double min, double max);

#endif