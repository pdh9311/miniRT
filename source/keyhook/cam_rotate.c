/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:54:11 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:54:12 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyhook.h"

static void	up_down_rotate(t_camera *cam, int up_down)
{
	t_vec3	r1;
	t_vec3	r2;

	cam->alpha = cam->rotate * up_down;
	r1 = multiply(cam->vector, cos(deg_to_rad(cam->alpha)));
	r2 = multiply(cam->v, sin(deg_to_rad(cam->alpha) * length(cam->vector)));
	cam->vector = add(r1, r2);
	cam->focal = add(cam->origin, \
				multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
	cam->w = unit_vector(subtract(cam->origin, cam->focal));
	cam->v = cross(cam->w, cam->u);
	cam->horizontal = multiply(cam->u, cam->vp_width);
	cam->vertical = multiply(cam->v, cam->vp_height);
}

static void	right_left_rotate(t_camera *cam, int right_left)
{
	t_vec3	r1;
	t_vec3	r2;

	cam->beta = cam->rotate * right_left;
	r1 = multiply(cam->vector, cos(deg_to_rad(cam->beta)));
	r2 = multiply(cam->u, sin(deg_to_rad(cam->beta) * length(cam->vector)));
	cam->vector = add(r1, r2);
	cam->focal = add(cam->origin, \
				multiply(unit_vector((t_vec3)cam->vector), cam->focal_length));
	cam->w = unit_vector(subtract(cam->origin, cam->focal));
	cam->u = unit_vector(cross(cam->vup, cam->w));
	cam->horizontal = multiply(cam->u, cam->vp_width);
	cam->vertical = multiply(cam->v, cam->vp_height);
}

static void	clockwise_rotate(t_camera *cam)
{
	cam->gamma = cam->z_rotate;
	cam->u = add(\
		multiply(cam->u, fabs(cos(deg_to_rad(cam->gamma))) * length(cam->u)), \
		multiply(cam->v, fabs(sin(deg_to_rad(cam->gamma))) * length(cam->u)));
	cam->v = cross(cam->w, cam->u);
	cam->horizontal = multiply(cam->u, cam->vp_width);
	cam->vertical = multiply(cam->v, cam->vp_height);
}

static void	counterclockwise_rotate(t_camera *cam)
{
	cam->gamma = -cam->z_rotate;
	cam->u = add(\
		multiply(cam->u, fabs(cos(deg_to_rad(cam->gamma))) * length(cam->u)), \
		multiply(negate(cam->v), \
				fabs(sin(deg_to_rad(cam->gamma))) * length(cam->u)));
	cam->v = cross(cam->w, cam->u);
	cam->horizontal = multiply(cam->u, cam->vp_width);
	cam->vertical = multiply(cam->v, cam->vp_height);
}

void	camera_rotate(t_camera *cam, int keycode)
{
	if (keycode == UP)
		up_down_rotate(cam, 1);
	else if (keycode == DOWN)
		up_down_rotate(cam, -1);
	else if (keycode == RIGHT)
		right_left_rotate(cam, 1);
	else if (keycode == LEFT)
		right_left_rotate(cam, -1);
	else if (keycode == PAGEUP)
		clockwise_rotate(cam);
	else if (keycode == PAGEDOWN)
		counterclockwise_rotate(cam);
}
