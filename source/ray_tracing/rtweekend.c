#include "rtweekend.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

double	random_double_(double min, double max)
{
	return (min + (max - min) * random_double());
}

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
