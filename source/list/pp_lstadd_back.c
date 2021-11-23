#include "list.h"

void	pp_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = pp_lstlast(*lst);
		new->next = last->next;
		new->prev = last;
		new->prev->next = new;
		if (new->next != NULL)
			new->next->prev = new;
	}
}
