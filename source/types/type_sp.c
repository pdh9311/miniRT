#include "element.h"
#include "libft.h"
#include <stdio.h>

int	input_type_sp(char **split)
{
	t_element	*elem;

	elem = (t_element *)malloc(sizeof(t_element));
	if (elem == NULL)
		return (EXIT_FAILURE);
	ft_memset(elem, 0, sizeof(t_element));
	elem->coord = set_coord(split[1]);
	elem->diameter = ft_atof(split[2]);
	elem->rgb = set_color(split[3]);
	// lst에 추가

	printf("%lf,%lf,%lf | %lf | %d %d %d\n", \
	elem->coord.x, elem->coord.y, elem->coord.z, \
	elem->diameter, \
	elem->rgb.r, elem->rgb.g, elem->rgb.b);
	return (EXIT_SUCCESS);
}