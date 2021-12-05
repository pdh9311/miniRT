#ifndef VEC3_H
# define VEC3_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define TRUE	1
# define FALSE	0

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

t_vec3	vec3_(double e1, double e2, double e3);
t_vec3	vec3_random(void);
t_vec3	vec3_random_(double min, double max);
void	update(t_vec3 *v, double e1, double e2, double e3);
t_vec3	negate(t_vec3 v);

int		near_zero(t_vec3 v);
t_vec3	multiply__(t_vec3 v, t_vec3 u);
void	multiply_(t_vec3 *v, double t);
t_vec3	multiply(t_vec3 v, double t);
void	divide_(t_vec3 *v, double t);

t_vec3	divide(t_vec3 v, double t);
double	length_squared(t_vec3 v);
double	length(t_vec3 v);
void	add_(t_vec3 *u, t_vec3 v);
t_vec3	add(t_vec3 u, t_vec3 v);

void	subtract_(t_vec3 *u, t_vec3 v);
t_vec3	subtract(t_vec3 u, t_vec3 v);
double	dot(t_vec3 u, t_vec3 v);
t_vec3	cross(t_vec3 u, t_vec3 v);
t_vec3	unit_vector(t_vec3 v);

t_vec3	random_in_unit_sphere(void);
t_vec3	random_unit_vector(void);
t_vec3	random_in_unit_disk(void);
t_vec3	reflect(t_vec3 v, t_vec3 n);
t_vec3	refract(t_vec3 uv, t_vec3 n, double etai_over_etat);

t_vec3	color_(double e1, double e2, double e3);
t_vec3	point3_(double e1, double e2, double e3);
t_vec3  random_unit_hemisphere(t_vec3 n);

typedef t_vec3	t_point3;
typedef t_vec3	t_color;

#endif