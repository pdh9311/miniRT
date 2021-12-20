#include <stdio.h>
#include "element.h"
#include "hit.h"
#include "miniRT.h"

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

static void print_obj_type(int type, t_hlist *hlist)
{
	if (type == 0)
		printf("type: none\n");
	if (type == 1)
		printf("type: plane\n");
	if (type == 2)
		printf("type: sphere\n");
	if (type == 3)
	{
		printf("type: cylinder\n");

		printf("point: [%lf %lf %lf]\n", ((t_cylinder *)(hlist->object.figure))->point.x,
			((t_cylinder *)(hlist->object.figure))->point.y, ((t_cylinder *)(hlist->object.figure))->point.z);

		printf("normal : [%lf %lf %lf]\n", ((t_cylinder *)(hlist->object.figure))->normal.x,
			((t_cylinder *)(hlist->object.figure))->normal.y, ((t_cylinder *)(hlist->object.figure))->normal.z);

		printf("unit_normal : [%lf %lf %lf]\n", ((t_cylinder *)(hlist->object.figure))->unit_normal.x,
			((t_cylinder *)(hlist->object.figure))->unit_normal.y, ((t_cylinder *)(hlist->object.figure))->unit_normal.z);

		printf("color : [%lf %lf %lf]\n", ((t_cylinder *)(hlist->object.figure))->color.x,
			((t_cylinder *)(hlist->object.figure))->color.y, ((t_cylinder *)(hlist->object.figure))->color.z);

		printf("albedo : [%lf %lf %lf]\n", ((t_cylinder *)(hlist->object.figure))->albedo.x,
			((t_cylinder *)(hlist->object.figure))->albedo.y, ((t_cylinder *)(hlist->object.figure))->albedo.z);

		printf("height : %lf\n", ((t_cylinder *)(hlist->object.figure))->height);
		printf("radius : %lf\n\n", ((t_cylinder *)(hlist->object.figure))->radius);
	}
	if (type == 4)
	{
		printf("type: cone\n");

		printf("point: [%lf %lf %lf]\n", ((t_cone *)(hlist->object.figure))->point.x,
			((t_cone *)(hlist->object.figure))->point.y, ((t_cone *)(hlist->object.figure))->point.z);

		printf("normal : [%lf %lf %lf]\n", ((t_cone *)(hlist->object.figure))->normal.x,
			((t_cone *)(hlist->object.figure))->normal.y, ((t_cone *)(hlist->object.figure))->normal.z);

		printf("unit_normal : [%lf %lf %lf]\n", ((t_cone *)(hlist->object.figure))->unit_normal.x,
			((t_cone *)(hlist->object.figure))->unit_normal.y, ((t_cone *)(hlist->object.figure))->unit_normal.z);

		printf("color : [%lf %lf %lf]\n", ((t_cone *)(hlist->object.figure))->color.x,
			((t_cone *)(hlist->object.figure))->color.y, ((t_cone *)(hlist->object.figure))->color.z);

		printf("albedo : [%lf %lf %lf]\n", ((t_cone *)(hlist->object.figure))->albedo.x,
			((t_cone *)(hlist->object.figure))->albedo.y, ((t_cone *)(hlist->object.figure))->albedo.z);

		printf("height : %lf\n", ((t_cone *)(hlist->object.figure))->height);
		printf("radius : %lf\n\n", ((t_cone *)(hlist->object.figure))->radius);
	}
}

void	print_obj_lst(t_hlist *hlist)
{
	while (hlist != NULL)
	{
		print_obj_type(hlist->object.type, hlist);
		hlist = hlist->next;
	}
}
