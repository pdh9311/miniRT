#include "keyhook.h"
#include "utils.h"

/*
	[ ADD in Linux or Ubuntu ]
	mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	mlx_destroy_image(scene->mlx.mlx_ptr, scene->mlx.img_ptr);
	mlx_destroy_display(scene->mlx.mlx_ptr);
	free(scene->mlx.mlx_ptr);
	system("leaks miniRT");	// memory leaks check in Mac
*/
int close_screen(void *param)
{
	t_hlist	*list;
	t_hlist	*tmp;
	t_scene *scene;

	scene = param;
	list = scene->list;
	while (list != NULL)
	{
		tmp = list->next;
		free(list->object.figure);
		free(list);
		list = tmp;
	}
	mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	// system("leaks miniRT");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	key_hook(int keycode, t_scene *scene)
{
	t_camera	*cam;
	double		x;
	double		y;
	double		z;

	cam = &scene->camera;
	x = scene->camera.origin.x;
	y = scene->camera.origin.y;
	z = scene->camera.origin.z;
	if (keycode == ESC)
		close_screen(scene);
	if (keycode == ENG_D)
	{
		cam->origin = add(cam->origin, multiply(cam->u, 0.1));
		// update(&cam->origin, x + 0.1, y, z);
	}
	else if (keycode == ENG_A)
	{
		cam->origin = add(cam->origin, multiply(cam->u, -0.1));
		// update(&cam->origin, x - 0.1, y, z);
	}
	else if (keycode == ENG_W)
	{
		cam->origin = add(cam->origin, multiply(cam->v, 0.1));
		// update(&cam->origin, x, y + 0.1, z);
	}
	else if (keycode == ENG_S)
	{
		cam->origin = add(cam->origin, multiply(cam->v, -0.1));
		// update(&cam->origin, x, y - 0.1, z);
	}
	else if (keycode == ENG_E)
	{
		cam->origin = add(cam->origin, multiply(unit_vector(cam->vector), -0.1));
		// update(&cam->origin, x, y, z + 0.1);
	}
	else if (keycode == ENG_Q)
	{
		cam->origin = add(cam->origin, multiply(unit_vector(cam->vector), 0.1));
		// update(&cam->origin, x, y, z - 0.1);
	}
	else if (keycode == BACKTIK)
	{
		update(&cam->origin, cam->origin2.x, cam->origin2.y, cam->origin2.z);
	}
	else if (keycode == ENG_P)
	{
		cam->origin = cam->origin2;
		cam->vector = cam->vector2;
	}
	else if (keycode == NUM_1) // x axis
	{
		++cam->alpha;
		cam->vector.y = -(sin(deg_to_rad(cam->alpha)));
		cam->vector.z = -(cos(deg_to_rad(cam->alpha)));
		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->u = unit_vector(cross(cam->vup, cam->w));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == NUM_2) // x axis
	{
		--cam->alpha;
		cam->vector.y = -(sin(deg_to_rad(cam->alpha)));
		cam->vector.z = -(cos(deg_to_rad(cam->alpha)));
		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->u = unit_vector(cross(cam->vup, cam->w));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == NUM_3)	// y axis
	{
		++cam->beta;
		cam->vector.x = -(sin(deg_to_rad(cam->beta)));
		cam->vector.z = -(cos(deg_to_rad(cam->beta)));
		//printf("%+.2lf %+.2lf %+.2lf\n", cam->vector.x, cam->vector.y, cam->vector.z);
		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->u = unit_vector(cross(cam->vup, cam->w));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == NUM_4) // y axis
	{
		--cam->beta;
		cam->vector.x = -(sin(deg_to_rad(cam->beta)));
		cam->vector.z = -(cos(deg_to_rad(cam->beta)));
		//printf("%+.2lf %+.2lf %+.2lf\n", cam->vector.x, cam->vector.y, cam->vector.z);
		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->u = unit_vector(cross(cam->vup, cam->w));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == NUM_5) // z axis
	{
		++cam->gamma;
		cam->vector.x = -(cos(deg_to_rad(cam->gamma)));
		cam->vector.y = -(sin(deg_to_rad(cam->gamma)));
		//printf("%+.2lf %+.2lf %+.2lf\n", cam->vector.x, cam->vector.y, cam->vector.z);
		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->u = unit_vector(cross(cam->vup, cam->w));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == NUM_6) // z axis
	{
		--cam->gamma;
		cam->vector.x = -(cos(deg_to_rad(cam->gamma)));
		cam->vector.y = -(sin(deg_to_rad(cam->gamma)));
		//printf("%+.2lf %+.2lf %+.2lf\n", cam->vector.x, cam->vector.y, cam->vector.z);
		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->u = unit_vector(cross(cam->vup, cam->w));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == UP)
	{
		cam->alpha += 10;
		t_vec3	r1 = multiply(cam->vector2, cos(deg_to_rad(cam->alpha)));
		t_vec3	r2 = multiply(cam->init_v, sin(deg_to_rad(cam->alpha) * length(cam->vector2)));
		t_vec3	r3 = multiply(cam->vector2, cos(deg_to_rad(cam->beta)));
		t_vec3	r4 = multiply(cam->init_u, sin(deg_to_rad(cam->beta) * length(cam->vector2)));
		cam->vector = add(add(r1, r2), add(r3, r4));
		// cam->vector = add(r1, r2);

		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->u = unit_vector(cross(cam->vup, cam->w));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == DOWN)
	{
		cam->alpha -= 10;
		t_vec3	r1 = multiply(cam->vector2, cos(deg_to_rad(cam->alpha)));
		t_vec3	r2 = multiply(cam->init_v, sin(deg_to_rad(cam->alpha) * length(cam->vector2)));
		t_vec3	r3 = multiply(cam->vector2, cos(deg_to_rad(cam->beta)));
		t_vec3	r4 = multiply(cam->init_u, sin(deg_to_rad(cam->beta) * length(cam->vector2)));
		cam->vector = add(add(r1, r2), add(r3, r4));
		// cam->vector = add(r1, r2);

		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->u = unit_vector(cross(cam->vup, cam->w));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == RIGHT)
	{
		cam->beta += 10;
		t_vec3	r1 = multiply(cam->vector2, cos(deg_to_rad(cam->alpha)));
		t_vec3	r2 = multiply(cam->init_v, sin(deg_to_rad(cam->alpha) * length(cam->vector2)));
		t_vec3	r3 = multiply(cam->vector2, cos(deg_to_rad(cam->beta)));
		t_vec3	r4 = multiply(cam->init_u, sin(deg_to_rad(cam->beta) * length(cam->vector2)));
		cam->vector = add(add(r1, r2), add(r3, r4));
		// cam->vector = add(r3, r4);

		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->u = unit_vector(cross(cam->vup, cam->w));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == LEFT)
	{
		cam->beta -= 10;
		t_vec3	r1 = multiply(cam->vector2, cos(deg_to_rad(cam->alpha)));
		t_vec3	r2 = multiply(cam->init_v, sin(deg_to_rad(cam->alpha) * length(cam->vector2)));
		t_vec3	r3 = multiply(cam->vector2, cos(deg_to_rad(cam->beta)));
		t_vec3	r4 = multiply(cam->init_u, sin(deg_to_rad(cam->beta) * length(cam->vector2)));
		cam->vector = add(add(r1, r2), add(r3, r4));
		// cam->vector = add(r3, r4);

		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->u = unit_vector(cross(cam->vup, cam->w));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	cam->lower_left_corner = subtract(
		subtract(subtract(cam->origin, divide(cam->horizontal, 2)),
			divide(cam->vertical, 2)), cam->w);

	printf("%+.2lf\t", cam->alpha);
	printf("%+.2lf\t", cam->beta);
	printf("%s%+.2lf %+.2lf %+.2lf%s\t", C_AQUA, scene->camera.vector.x, scene->camera.vector.y, scene->camera.vector.z, C_NC);
	printf("%s%+.2lf %+.2lf %+.2lf%s\t", C_RED, scene->camera.u.x, scene->camera.u.y, scene->camera.u.z, C_NC);
	printf("%s%+.2lf %+.2lf %+.2lf%s\t", C_GREEN, scene->camera.v.x, scene->camera.v.y, scene->camera.v.z, C_NC);
	printf("%s%+.2lf %+.2lf %+.2lf%s\t", C_BLUE, scene->camera.w.x, scene->camera.w.y, scene->camera.w.z, C_NC);
	printf("%s%+.2lf %+.2lf %+.2lf%s\n", C_RED, scene->camera.origin.x, scene->camera.origin.y, scene->camera.origin.z, C_NC);

	// printf("%s%+.2lf %+.2lf %+.2lf%s\n", C_BLUE, \
	// 		((t_sphere *)(scene->list->object.figure))->center.x,\
	// 		((t_sphere *)(scene->list->object.figure))->center.y, \
	// 		((t_sphere *)(scene->list->object.figure))->center.z, C_NC);
	return (0);
}
