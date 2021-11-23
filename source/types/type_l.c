#include "element.h"
#include "libft.h"
#include <stdio.h>

int	input_type_l(char **split, t_lst **lst)
{
	t_element	*elem;

	elem = (t_element *)malloc(sizeof(t_element));
	if (elem == NULL)
		return (EXIT_FAILURE);
	ft_memset(elem, 0, sizeof(t_element));
	elem->coord = get_coord(split[1]);
	elem->brightness = ft_atof(split[2]);
	elem->rgb = get_color(split[3]);
	elem->type = L;
	// lst에 추가
	pp_lstadd_back(lst, pp_lstnew(elem));
	// printf("%lf,%lf,%lf | %lf | %d %d %d\n", \
	// elem->coord.x, elem->coord.y, elem->coord.z, \
	// elem->brightness, \
	// elem->rgb.r, elem->rgb.g, elem->rgb.b);
	return (EXIT_SUCCESS);
}