#ifndef HITTABLE_LIST_H
# define HITTABLE_LIST_H

# include "hittable.h"
# include "sphere.h"
# include "moving_sphere.h"

typedef struct	s_hlist
{
	t_hittable		object;
	struct s_hlist	*next;
}				t_hlist;

t_hlist	*list_(t_hittable object)
{
	t_hlist	*new_node;

	new_node = (t_hlist *)malloc(sizeof(t_hlist));
	if (new_node)
	{
		new_node->object = object;
		new_node->next = NULL;
	}
	return (new_node);
}

void	push(t_hlist **lst, t_hlist *new_node)
{
	t_hlist	*temp;

	temp = *lst;
	*lst = new_node;
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

static int hit_(t_hittable *object, t_ray *r, double t_min, double t_max, t_hit_record *rec)
{
	int	is_hit;

	switch (object->geometry)
	{
		case _sphere:
			is_hit = hit_sphere((t_sphere*)object->pointer, r, t_min, t_max, rec);
			break;
		case _moving_sphere:
			is_hit = hit_moving_sphere((t_moving_sphere*)object->pointer, r, t_min, t_max, rec);
			break;
	}
	if (is_hit)
		rec->material = object->material;
	return (is_hit);
}

int hit(t_hlist *current, t_ray *r, double t_min, double t_max, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	double			closest_so_far;
	int				hit_anything;
	
	hit_anything = FALSE;
	closest_so_far = t_max;
	while (current)
	{
		if (hit_(&current->object, r, t_min, t_max, &temp_rec))
			if (temp_rec.t < closest_so_far)
			{
				hit_anything = TRUE;
				closest_so_far = temp_rec.t; 
				*rec = temp_rec;
			}
		current = current->next;
	}
	return (hit_anything);
}

#endif