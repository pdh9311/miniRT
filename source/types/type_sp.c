#include "element.h"
#include "libft.h"

int	input_type_sp(char **split, t_lst **lst)
{
	t_element	*elem;

	if (split_cnt(split) != 4)
	{
		ft_putendl_fd("Error\n  Wrong argument count sp", 2);
		return (EXIT_FAILURE);
	}
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
	pp_lstadd_back(lst, pp_lstnew(elem));
	return (EXIT_SUCCESS);
}
