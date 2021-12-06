#include "camera.h"

void	init_camera(t_camera *cam)
{
	cam->aspect_ratio = 16.0 / 9.0;
	cam->image_width = 800;
	cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
	cam->samples_per_pixel = 20;
	cam->focal_length = 1.0;
	cam->vp_height = 2.0;
	cam->vp_width = cam->aspect_ratio * cam->vp_height;
	cam->origin = (t_vec3){0.0, 0.0, 0.0};
	cam->horizontal = (t_vec3){cam->vp_width, 0.0, 0.0};
	cam->vertical = (t_vec3){0.0, cam->vp_height, 0.0};
	cam->focal = (t_vec3){0.0, 0.0, cam->focal_length};
	cam->lower_left_corner = subtract(
		subtract(
			subtract(cam->origin, divide(cam->horizontal, 2)),
			divide(cam->vertical, 2)
		),
		cam->focal
	);
}