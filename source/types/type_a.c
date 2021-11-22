#include "element.h"
#include "libft.h"
#include <stdio.h>	//

int	input_type_a(char **split)
{
	t_element	*elem;

	elem = (t_element *)malloc(sizeof(t_element));
	if (elem == NULL)
		return (EXIT_FAILURE);
	ft_memset(elem, 0, sizeof(t_element));
	elem->brightness = ft_atof(split[1]);
	elem->rgb = set_color(split[2]);
	// lst에 추가
	printf("%lf | %d %d %d\n", elem->brightness, elem->rgb.r, elem->rgb.g, elem->rgb.b);
	return (EXIT_SUCCESS);	
}