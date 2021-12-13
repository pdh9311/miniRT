#include "element.h"
#include "libft.h"
#include <stdio.h>	//

int	input_type_a(char **split, t_lst **lst)
{
	t_element	*elem;

	elem = (t_element *)malloc(sizeof(t_element));
	if (elem == NULL)
		return (EXIT_FAILURE);
	ft_memset(elem, 0, sizeof(t_element));
	elem->coord = (t_point3){0, 0, 0};
	elem->brightness = ft_atof(split[1]);
	elem->rgb = get_color(split[2]);
	elem->type = A;
	// lst에 추가
	pp_lstadd_back(lst, pp_lstnew(elem));
	// printf("%lf | %d %d %d\n", elem->brightness, elem->rgb.r, elem->rgb.g, elem->rgb.b);
	return (EXIT_SUCCESS);	
}