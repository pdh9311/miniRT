/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:12 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:12 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * ksn : shininess value
 * ks : specular strength
 */
void	set_specular(t_color *pixel_color, t_scene *scene, \
						t_hit_record *rec, t_phong *phong)
{
	phong->ksn = 128;
	phong->ks = 0.5;
	phong->view_dir = unit_vector(negate(scene->ray.direction));
	phong->reflect_dir = reflect(phong->light_unit_dir, rec->normal);
	phong->spec = pow(fmax(dot(phong->view_dir, phong->reflect_dir), 0.0), \
						phong->ksn);
	phong->specular = multiply(*pixel_color, phong->ks * phong->spec);
	add_(pixel_color, phong->specular);
	vec_min(pixel_color, (t_color){1.0, 1.0, 1.0});
}
