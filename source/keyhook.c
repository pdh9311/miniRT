#include "keyhook.h"
#include "utils.h"

double	g_alpha;
double	g_beta;
double	g_gamma;

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
	if (keycode == ENG_D)	// right
		cam->origin = add(cam->origin, multiply(cam->u, 0.1));
	else if (keycode == ENG_A)	// left
		cam->origin = add(cam->origin, multiply(cam->u, -0.1));
	else if (keycode == ENG_W)	// up
		cam->origin = add(cam->origin, multiply(cam->v, 0.1));
	else if (keycode == ENG_S)	// down
		cam->origin = add(cam->origin, multiply(cam->v, -0.1));
	else if (keycode == ENG_E)	//front
		cam->origin = add(cam->origin, multiply(unit_vector(cam->vector), -0.1));
	else if (keycode == ENG_Q)	// back
		cam->origin = add(cam->origin, multiply(unit_vector(cam->vector), 0.1));
	else if (keycode == BACKTIK)
	{
		update(&cam->origin, cam->origin2.x, cam->origin2.y, cam->origin2.z);
	}
	else if (keycode == ENG_P)
	{
		cam->origin = cam->origin2;
		cam->vector = cam->vector2;
	}
	else if (keycode == UP)
	{
		cam->alpha = 5;
		g_alpha += cam->alpha;
		t_vec3	r1 = multiply(cam->vector, cos(deg_to_rad(cam->alpha)));
		t_vec3	r2 = multiply(cam->v, sin(deg_to_rad(cam->alpha) * length(cam->vector)));
		cam->vector = add(r1, r2);
		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == DOWN)
	{
		cam->alpha = -5;
		g_alpha += cam->alpha;
		t_vec3	r1 = multiply(cam->vector, cos(deg_to_rad(cam->alpha)));
		t_vec3	r2 = multiply(cam->v, sin(deg_to_rad(cam->alpha) * length(cam->vector)));
		cam->vector = add(r1, r2);
		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == RIGHT)
	{
		cam->beta = 5;
		g_beta += cam->beta;
		t_vec3	r1 = multiply(cam->vector, cos(deg_to_rad(cam->beta)));
		t_vec3	r2 = multiply(cam->u, sin(deg_to_rad(cam->beta) * length(cam->vector)));
		cam->vector = add(r1, r2);
		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->u = unit_vector(cross(cam->vup, cam->w));
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == LEFT)
	{
		cam->beta = -5;
		g_beta += cam->beta;
		t_vec3	r1 = multiply(cam->vector, cos(deg_to_rad(cam->beta)));
		t_vec3	r2 = multiply(cam->u, sin(deg_to_rad(cam->beta) * length(cam->vector)));
		cam->vector = add(r1, r2);
		cam->focal = add(cam->origin, multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
		cam->w = unit_vector(subtract(cam->origin, cam->focal));
		cam->u = unit_vector(cross(cam->vup, cam->w));
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == PAGEUP)
	{
		cam->gamma = 5;
		g_gamma += cam->gamma;
		// cam->u = unit_vector(cross(cam->vup, cam->w));
		// cam->v = cross(cam->w, cam->u);
		// printf("u: %+.3lf %+.3lf %+.3lf\n", scene->camera.u.x, scene->camera.u.y, scene->camera.u.z);
		// printf("v: %+.3lf %+.3lf %+.3lf\n", scene->camera.v.x, scene->camera.v.y, scene->camera.v.z);
		// printf("%lf \n", cos(deg_to_rad(cam->gamma)));
		// printf("%lf \n", sin(deg_to_rad(cam->gamma)));
		// printf("%lf %lf %lf\n", multiply(cam->u, cos(deg_to_rad(cam->gamma)) * length(cam->u)).x, \
		// 						multiply(cam->u, cos(deg_to_rad(cam->gamma)) * length(cam->u)).y, \
		// 						multiply(cam->u, cos(deg_to_rad(cam->gamma)) * length(cam->u)).z);
		// printf("%lf %lf %lf\n", multiply(cam->v, sin(deg_to_rad(cam->gamma)) * length(cam->u)).x, \
		// 						multiply(cam->v, sin(deg_to_rad(cam->gamma)) * length(cam->u)).y, \
		// 						multiply(cam->v, sin(deg_to_rad(cam->gamma)) * length(cam->u)).z);
		cam->u = add(multiply(cam->u, fabs(cos(deg_to_rad(cam->gamma))) * length(cam->u)), \
					multiply(cam->v, fabs(sin(deg_to_rad(cam->gamma))) * length(cam->u)));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	else if (keycode == PAGEDOWN)
	{
		cam->gamma = -5;
		g_gamma += cam->gamma;
		cam->u = add(multiply(cam->u, fabs(cos(deg_to_rad(cam->gamma))) * length(cam->u)), \
					multiply(negate(cam->v), fabs(sin(deg_to_rad(cam->gamma))) * length(cam->u)));
		cam->v = cross(cam->w, cam->u);
		cam->horizontal = multiply(cam->u, cam->vp_width);
		cam->vertical = multiply(cam->v, cam->vp_height);
	}
	cam->lower_left_corner = subtract(
		subtract(subtract(cam->origin, divide(cam->horizontal, 2)),
			divide(cam->vertical, 2)), cam->w);
	// cam->lower_left_corner = add(cam->origin, add(cam->focal, add(divide(cam->horizontal, -2), divide(cam->vertical, -2))));
	printf("%+.2lf\t", g_alpha);
	printf("%+.2lf\t", g_beta);
	printf("%+.2lf\t", g_gamma);
	printf("%s%+.3lf %+.3lf %+.3lf%s\t", C_AQUA, scene->camera.vector.x, scene->camera.vector.y, scene->camera.vector.z, C_NC);
	printf("%s%+.3lf %+.3lf %+.3lf%s\t", C_RED, scene->camera.u.x, scene->camera.u.y, scene->camera.u.z, C_NC);
	printf("%s%+.3lf %+.3lf %+.3lf%s\t", C_GREEN, scene->camera.v.x, scene->camera.v.y, scene->camera.v.z, C_NC);
	printf("%s%+.3lf %+.3lf %+.3lf%s\t", C_BLUE, scene->camera.w.x, scene->camera.w.y, scene->camera.w.z, C_NC);
	printf("%s%+.3lf %+.3lf %+.3lf%s\t", C_YELLOW, scene->camera.origin.x, scene->camera.origin.y, scene->camera.origin.z, C_NC);
	printf("%s%+.3lf %+.3lf %+.3lf%s\n", C_PURPLE, cam->lower_left_corner.x, cam->lower_left_corner.y, cam->lower_left_corner.z, C_NC);
	// printf("%s%+.3lf %+.3lf %+.3lf%s\n", C_BLUE, \
	// 		((t_sphere *)(scene->list->object.figure))->center.x,\
	// 		((t_sphere *)(scene->list->object.figure))->center.y, \
	// 		((t_sphere *)(scene->list->object.figure))->center.z, C_NC);
	return (0);
}
