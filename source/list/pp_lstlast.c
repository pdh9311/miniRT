#include "list.h"

t_lst	*pp_lstlast(t_lst *lst)
{
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
