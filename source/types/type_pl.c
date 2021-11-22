#include "element.h"
#include "libft.h"
#include <stdio.h>

int	input_type_pl(char **split)
{
	t_element	*elem;

	elem = (t_element *)malloc(sizeof(t_element));
	if (elem == NULL)
		return (EXIT_FAILURE);
	ft_memset(elem, 0, sizeof(t_element));
	elem->coord = set_coord(split[1]);
	elem->vector = set_coord(split[2]);
	elem->rgb = set_color(split[3]);
	// lst에 추가

	printf("%lf,%lf,%lf | %lf,%lf,%lf | %d %d %d\n", \
	elem->coord.x, elem->coord.y, elem->coord.z, \
	elem->vector.x, elem->vector.y, elem->vector.z, \
	elem->rgb.r, elem->rgb.g, elem->rgb.b);
	return (EXIT_SUCCESS);
}