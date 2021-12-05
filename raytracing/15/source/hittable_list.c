#include "hittable_list.h"
#include <stdlib.h>

t_hlist	*list_(t_hittable object)
{
	t_hlist	*new;

	new = malloc(sizeof(t_hlist));
	if (new)
	{
		new->object = object;
		new->next = NULL;
	}
	return (new);
}

void	push(t_hlist **lst, t_hlist *new)
{
	t_hlist	*temp;

	temp = *lst;
	*lst = new;
	(*lst)->next = temp;
}

void	drop(t_hlist *lst)
{
	if (lst)
	{
		free(lst->object.pointer);
		free(lst);
	}
}

void	clear(t_hlist **lst)
{
	t_hlist	*temp;

	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			drop(*lst);
			(*lst) = temp;
		}
		lst = NULL;
	}
}

static int hit_(t_hittable *object, t_ray r, double t_min, double t_max, t_hit_record *rec)
{
	int is_hit;

	is_hit = FALSE;
	if (object->geometry == _sphere) {
		is_hit = hit_sphere(object->pointer, r, t_min, t_max, rec);
	}
	if (is_hit)
		rec->material = object->material;
	return (is_hit);
}

int hit(t_hlist *current, t_ray r, double t_min, double t_max, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	double			closest_so_far = t_max;
	int				hit_anything = FALSE;

	while (current)
	{
		if (hit_(&current->object, r, t_min, t_max, &temp_rec)) {	// 광선과 부딪히는 물체가 있다면
			if (temp_rec.t < closest_so_far) {	// 광선과 가장 가까운 t값을 가져오기위해 판별한다.
				hit_anything = TRUE;			// 광선과 부딪히는 물체가 있다면 TRUE
				closest_so_far = temp_rec.t;
				*rec = temp_rec;
			}
		}
		current = current->next;
	}
	return (hit_anything);
}
