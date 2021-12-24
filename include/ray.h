/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:58:29 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:58:29 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
t_point3	at(const t_ray *r, float t);
t_vec3		new_ray_dir(t_camera *cam, float u, float v);

#endif
