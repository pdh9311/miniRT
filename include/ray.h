#ifndef RAY_H
# define RAY_H

# include "vec3.h"
# include "camera.h"

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
}				t_ray;

t_ray		ray_(t_point3 origin, t_vec3 direction);
t_point3	at(const t_ray *r, double t);
t_vec3		new_ray_dir(t_camera *cam, double u, double v);

#endif