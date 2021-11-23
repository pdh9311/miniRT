#include "list.h"

void	pp_lstdelone(t_lst *lst)
{
	if (lst == NULL)
		return ;
	if (lst->prev != NULL)
		lst->prev->next = lst->next;
	if (lst->next != NULL)
		lst->next->prev = lst->prev;
	free(lst->content);
	free(lst);
}
