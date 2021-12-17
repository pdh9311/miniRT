#ifndef CAMERA_H
# define CAMERA_H
# include "vec3.h"

typedef struct s_camera
{
	float		aspect_ratio;
	int			image_width;
	int			image_height;
	t_vec3		origin;
	t_vec3		origin2;
	t_vec3		vector;
	t_vec3		vector2;
	float		fov;
	float		vp_height;
	float		vp_width;
	t_vec3		vup;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;
	t_vec3		init_w;
	t_vec3		init_u;
	t_vec3		init_v;
	float		focal_length;
	int			samples_per_pixel;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		focal;
	t_vec3		lower_left_corner;
	float		alpha;
	float		beta;
	float		gamma;
}				t_camera;

#endif
