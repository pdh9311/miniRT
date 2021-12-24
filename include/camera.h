/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:59 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:59 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "vec3.h"

typedef struct s_camera
{
	float		aspect_ratio;
	int			image_width;
	int			image_height;
	t_vec3		origin;
	t_vec3		vector;
	float		fov;
	float		vp_height;
	float		vp_width;
	t_vec3		vup;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;
	float		focal_length;
	int			samples_per_pixel;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		focal;
	t_vec3		lower_left_corner;
	float		alpha;
	float		beta;
	float		gamma;
	float		move;
	float		rotate;
	float		z_rotate;
}				t_camera;

#endif
