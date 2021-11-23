#include <stdio.h>
#include "element.h"

void	print_str_arr(char **str_arr)
{	
	int	i;

	i = 0;
	while (str_arr[i])
	{
		printf("%s\t", str_arr[i]);
		i++;
	}
	printf("\n");
}

/**
	t_check		check;
	t_coord		coord;
	t_coord		vector;
	t_color		rgb;
	double		brightness;
	double		diameter;
	double		height;
	double		fov;
    int			type;
 */
# define CONT ((t_element *)(lst->content))
void	print_lst(t_lst *lst)
{
	while (lst != NULL)
	{
		printf("coord : [%lf, %lf, %lf]\n", CONT->coord.x, CONT->coord.y, CONT->coord.z);
		printf("vector : [%lf, %lf, %lf]\n", CONT->vector.x, CONT->vector.y, CONT->vector.z);
		printf("rgb : [%d, %d, %d]\n", CONT->rgb.r, CONT->rgb.g, CONT->rgb.b);
		printf("brightness : %lf\n", CONT->brightness);
		printf("diameter : %lf\n", CONT->diameter);
		printf("height : %lf\n", CONT->height);
		printf("fov : %lf\n", CONT->fov);
		printf("type : %d\n\n", CONT->type);
		lst = lst->next;
	}
}