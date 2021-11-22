#include "element.h"
#include "libft.h"
#include <stdio.h>	//

int	input_type_c(char **split)
{
	t_element	*elem;

	elem = (t_element *)malloc(sizeof(t_element));
	if (elem == NULL)
		return (EXIT_FAILURE);
	ft_memset(elem, 0, sizeof(t_element));
	elem->coord = set_coord(split[1]);
	elem->vector = set_coord(split[2]);
	elem->fov = ft_atof(split[3]);
	// lst에 추가
	printf("%lf,%lf,%lf | %lf,%lf,%lf, | %lf\n", elem->coord.x, elem->coord.y, elem->coord.z,\
		elem->vector.x, elem->vector.y, elem->vector.z, elem->fov);
	return (EXIT_SUCCESS);	
}	