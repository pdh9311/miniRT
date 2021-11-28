#ifndef VEC3_H
# define VEC3_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

# define TURE	1
# define FALSE	0

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

// vec3 생성 시 (e1, e2, e3)인 vec3를 반환한다.
t_vec3	vec3(double e1, double e2, double e3);

// 각 좌표의 값을 반환하는 함수
double	vec3_x(t_vec3 vec3);
double	vec3_y(t_vec3 vec3);
double	vec3_z(t_vec3 vec3);

// vec3 operator
void	vec_negative(t_vec3 *vec3);
void	vec_addition(t_vec3 *vec3, t_vec3 v);
void	vec_multiply(t_vec3 *vec3, double t);
void	vec_division(t_vec3 *vec3, double t);

double	vec_length(t_vec3 vec3);
double	vec_length_squared(t_vec3 vec3);


#endif
