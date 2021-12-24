/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:58:35 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:58:35 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define TRUE	1
# define FALSE	0

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

t_vec3	vec3_(float e1, float e2, float e3);
t_vec3	vec3_random(void);
t_vec3	vec3_random_(float min, float max);
void	update(t_vec3 *v, float e1, float e2, float e3);
t_vec3	negate(t_vec3 v);

int		near_zero(t_vec3 v);
t_vec3	multiply__(t_vec3 v, t_vec3 u);
void	multiply_(t_vec3 *v, float t);
t_vec3	multiply(t_vec3 v, float t);
void	divide_(t_vec3 *v, float t);

t_vec3	divide(t_vec3 v, float t);
float	length_squared(t_vec3 v);
float	length(t_vec3 v);
void	add_(t_vec3 *u, t_vec3 v);
t_vec3	add(t_vec3 u, t_vec3 v);

void	subtract_(t_vec3 *u, t_vec3 v);
t_vec3	subtract(t_vec3 u, t_vec3 v);
float	dot(t_vec3 u, t_vec3 v);
t_vec3	cross(t_vec3 u, t_vec3 v);
t_vec3	unit_vector(t_vec3 v);

t_vec3	random_in_unit_sphere(void);
t_vec3	random_unit_vector(void);
t_vec3	random_in_unit_disk(void);
t_vec3	reflect(t_vec3 v, t_vec3 n);
t_vec3	refract(t_vec3 uv, t_vec3 n, float etai_over_etat);

t_vec3	color_(float e1, float e2, float e3);
t_vec3	point3_(float e1, float e2, float e3);
t_vec3	random_unit_hemisphere(t_vec3 n);
void	vec_min(t_vec3 *v, t_vec3 max);

typedef t_vec3	t_point3;
typedef t_vec3	t_color;

#endif
