#include "element.h"
#include "libft.h"
#include <stdio.h>	//

/** C(카메라)
 * x, y, z 좌표
 * 3d vector 값[-1, 1] x, y, z 좌표 당 하나 씩 총 3개
 * 화각[0, 180]
 */
int	input_type_c(char **split, t_lst **lst)
{
	t_element	*elem;

	elem = (t_element *)malloc(sizeof(t_element));
	if (elem == NULL)
		return (EXIT_FAILURE);
	ft_memset(elem, 0, sizeof(t_element));
	elem->coord = get_coord(split[1]);
	elem->vector = get_coord(split[2]);
	elem->fov = ft_atof(split[3]);
	elem->type = C;
	// lst에 추가
	pp_lstadd_back(lst, pp_lstnew(elem));
	// printf("%lf,%lf,%lf | %lf,%lf,%lf, | %lf\n", elem->coord.x, elem->coord.y, elem->coord.z,\
		// elem->vector.x, elem->vector.y, elem->vector.z, elem->fov);
	return (EXIT_SUCCESS);
}
