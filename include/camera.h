#ifndef CAMERA_H
# define CAMERA_H
# include "vec3.h"

typedef struct s_camera
{
	double		aspect_ratio;
	int			image_width;
	int			image_height;
	t_vec3		origin;
	double		fov;
	double		vp_height;
	double		vp_width;
	t_vec3		vup;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;
	double		focal_length;
	int			samples_per_pixel;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		focal;
	t_vec3		lower_left_corner;
}				t_camera;

#endif