#include <stdio.h>
#include "element.h"

# define CONT ((t_element *)(lst->content))

static void	print_type(int type)
{
	if (type == 0)
		printf("type : A\n");
	else if (type == 1)
		printf("type : C\n");
	else if (type == 2)
		printf("type : L\n");
	else if (type == 3)
		printf("type : PL\n");
	else if (type == 4)
		printf("type : SP\n");
	else if (type == 5)
		printf("type : CY\n");
	else if (type == 6)
		printf("type : CO\n");
}

void	print_lst(t_lst *lst)
{
	while (lst != NULL)
	{
		print_type(CONT->type);
		printf("coord : [%lf, %lf, %lf]\n", CONT->coord.x, CONT->coord.y, CONT->coord.z);
		printf("vector : [%lf, %lf, %lf]\n", CONT->vector.x, CONT->vector.y, CONT->vector.z);
		printf("rgb : [%lf, %lf, %lf]\n", CONT->rgb.x, CONT->rgb.y, CONT->rgb.z);
		printf("brightness : %lf\n", CONT->brightness);
		printf("diameter : %lf\n", CONT->diameter);
		printf("height : %lf\n", CONT->height);
		printf("fov : %lf\n\n", CONT->fov);
		lst = lst->next;
	}
}
