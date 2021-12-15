#include "element.h"
#include "libft.h"
#include <stdio.h>

int	input_type_sp(char **split, t_lst **lst)
{
	t_element	*elem;

	elem = (t_element *)malloc(sizeof(t_element));
	if (elem == NULL)
		return (EXIT_FAILURE);
	ft_memset(elem, 0, sizeof(t_element));
	elem->coord = get_point3(split[1]);
	elem->diameter = ft_atof(split[2]);
	elem->rgb = get_color(split[3]);
	elem->type = SP;
	if (elem->diameter < 0 || check_rgb(elem->rgb))
	{
		free(elem);
		ft_putendl_fd("Error\n  Not in range", 2);
		return (EXIT_FAILURE);
	}
	// lst에 추가
	pp_lstadd_back(lst, pp_lstnew(elem));
	/*
	printf("%lf,%lf,%lf | %lf | %d %d %d\n", \
	elem->coord.x, elem->coord.y, elem->coord.z, \
	elem->diameter, \
	elem->rgb.r, elem->rgb.g, elem->rgb.b);
	*/
	return (EXIT_SUCCESS);
}
