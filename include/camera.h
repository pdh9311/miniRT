#ifndef CAMERA_H
# define CAMERA_H
# include "vec3.h"

typedef struct s_camera
{
	double		aspect_ratio;
	double		vp_width;
	double		vp_height;
	double		focal_length;
	int			image_width;
	int			image_height;
	int			samples_per_pixel;
	t_vec3		origin;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		focal;
	t_vec3		lower_left_corner;
}				t_camera;

#endif