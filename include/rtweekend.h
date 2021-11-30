#ifndef RTWEEKEND_H
# define RTWEEKEND_H

# include <math.h>
# include <stdlib.h>
# include "ray.h"
# include "vec3.h"

double	degrees_to_radians(double degrees);
double	random_double(void);
double	random_double_(double min, double max);
double	clamp(double x, double min, double max);

#endif