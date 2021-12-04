#include "sphere.h"
#include <stdlib.h>
#include <math.h>

int hit_sphere(t_sphere *s, t_ray r, double t_min, double t_max, t_hit_record *rec)
{
	t_vec3 oc = subtract(r.origin, s->center);
	double a = length_squared(r.direction);
	double half_b = dot(r.direction, oc);
	double c = length_squared(oc) - (s->radius * s->radius);

	double discriminant = half_b*half_b - a*c;
	if (discriminant < 0)
		return (FALSE);
	// 허용 범위 안에 가장 가까운 해가 있는지 확인한다.
	double sqrtd = sqrt(discriminant);
	double root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return (FALSE);
	}
	// 허용범위에 있을때
	rec->t = root;				// 광선과 구가 교차한다.
	rec->p = at(&r, rec->t);	// 광선과 구가 교차하는 점
	t_vec3 outward_normal = divide(subtract(rec->p, s->center), s->radius);	// 광선과 구가 교차하는 점에서의 법선 벡터의 단위 벡터
	set_face_normal(rec, r, outward_normal);

	return (TRUE);
}

