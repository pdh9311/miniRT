/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:56:48 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 16:02:36 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_diffuse(t_color *pixel_color, t_scene *scene, \
				t_hit_record *rec, t_phong *phong)
{
	t_color		diffuse;

	phong->light_dir = subtract(scene->light->origin, rec->p);
	phong->light_unit_dir = unit_vector(phong->light_dir);
	phong->kd = fmax(dot(rec->normal, phong->light_unit_dir), 0.0);
	diffuse = multiply(multiply(scene->light->color, \
						scene->light->bright_ratio), phong->kd);
	add_(pixel_color, diffuse);
}
