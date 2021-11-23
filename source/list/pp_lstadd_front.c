#include "list.h"

void	pp_lstadd_front(t_lst **lst, t_lst *new)
{
	t_lst	*begin;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		begin = *lst;
		new->next = begin;
		new->prev = begin->prev;
		if (new->prev != NULL)
			new->prev->next = new;
		new->next->prev = new;
	}
}
