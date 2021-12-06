#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include "camera.h"
# include "mlx.h"
# include "ray.h"
# include "sphere.h"

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			size_l;
	int			endian;
	t_color		pixel_color;
	int			rgb[3];
	int			color;
}				t_mlx;

typedef struct s_light
{
	t_point3	origin;
	t_color		color;
	double		bright_ratio;
}				t_light;

typedef struct s_scene
{
	t_mlx		mlx;
	t_camera	camera;
	t_light		light; // Ambient
}				t_scene;

// init.c
void	init(t_scene *scene);

// random_clamp.c
double	degrees_to_radians(double degrees);
double	random_double(void);
double	random_double_(double min, double max);
double	clamp(double x, double min, double max);

#endif