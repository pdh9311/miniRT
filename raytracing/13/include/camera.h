#ifndef CAMERA_H
# define CAMERA_H

# include "rtweekend.h"
# include "vec3.h"
# include "ray.h"

typedef struct t_camera
{
	t_point3	origin;
	t_point3	lower_left_corner;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		w, u, v;
	double		lens_radius;
	double		time0, time1;
}	t_camera;

t_camera	camera_(t_point3 lookfrom, t_point3 lookat, t_vec3 vup, double vfov, \
					double aspect_ratio, double aperture, double focus_dist, double time0, double time1);
t_ray		get_ray(t_camera *c, double s, double t);
#endif
