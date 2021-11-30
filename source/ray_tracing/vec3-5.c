#include "rtweekend.h"

t_vec3 random_in_unit_sphere()
{
	while (TRUE)
	{
		t_vec3 p = vec3_random_(-1,1);
		if (length_squared(p) >= 1)
			continue;
		return (p);
	}
}

t_vec3 random_unit_vector()
{
	return (unit_vector(random_in_unit_sphere()));
}

t_vec3 random_in_unit_disk()
{
	while (TRUE)
	{
		t_vec3 p = vec3_(random_double_(-1,1), random_double_(-1,1), 0);
		if (length_squared(p) >= 1)
			continue;
		return (p);
	}
}

t_vec3 reflect(t_vec3 v, t_vec3 n)
{
	return (subtract(v, multiply(n, 2*dot(v,n))));
}

t_vec3 refract(t_vec3 uv, t_vec3 n, double etai_over_etat)
{
	double cos_theta = fmin(dot(negate(uv), n), 1.0);
	t_vec3 r_out_perp = multiply(add(uv, multiply(n, cos_theta)), etai_over_etat);
	t_vec3 r_out_parallel = multiply(n, -sqrt(fabs(1.0 - length_squared(r_out_perp))));
	return (add(r_out_perp, r_out_parallel));
}