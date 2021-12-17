#include "miniRT.h"

void	set_camera(t_scene *scene)
{
	t_camera	**cam;
	t_lst		**cam_list_move_tmp;

	cam = &scene->camera;
	cam_list_move_tmp = &scene->cam_list_move;
	*cam_list_move_tmp = scene->cam_list;
	*cam = (t_camera *)scene->cam_list_move->content;
}

// add only *** 1 camera ***
int	make_cam_list(t_scene *scene, t_element *elem)
{
	t_camera	*cam;
	t_lst		*new_cam;
	t_lst		**cam_list_tmp;

	cam = (t_camera *)malloc(sizeof(t_camera));
	if (cam == NULL)
		return (EXIT_FAILURE);
	init_camera(cam, elem);
	cam_list_tmp = &(scene->cam_list);
	new_cam = pp_lstnew((void *)cam);
	pp_lstadd_back(cam_list_tmp, new_cam);
	return (EXIT_SUCCESS);
}

void	init_camera(t_camera *cam, t_element *elem)
{
	cam->aspect_ratio = 16.0 / 9.0;
	cam->image_width = 800;
	cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
	cam->samples_per_pixel = 20;
	cam->focal_length = 1.0;
	cam->vup = (t_vec3){0, 1, 0};
	cam->fov = elem->fov;
	cam->alpha = 0;
	cam->beta = 0;
	cam->gamma = 0;
	cam->move = 1;
	cam->rotate = 5;
	cam->z_rotate = 90;

	cam->origin = elem->coord;
	cam->vector = elem->vector;
	cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)elem->vector), cam->focal_length));
	cam->vp_height = 2 * cam->focal_length * tan(deg_to_rad(elem->fov / 2));
	cam->vp_width = cam->aspect_ratio * cam->vp_height;
	cam->w = unit_vector(subtract(cam->origin, cam->focal));
	cam->u = unit_vector(cross(cam->vup, cam->w));
	cam->v = cross(cam->w, cam->u);
	cam->horizontal = multiply(cam->u, cam->vp_width);
	cam->vertical = multiply(cam->v, cam->vp_height);
	cam->lower_left_corner = subtract(
			subtract(subtract(cam->origin, divide(cam->horizontal, 2)),
				divide(cam->vertical, 2)), cam->w);
	cam->origin2 = elem->coord;
	cam->vector2 = elem->vector;
	cam->init_w = cam->w;
	cam->init_u = cam->u;
	cam->init_v = cam->v;
}
