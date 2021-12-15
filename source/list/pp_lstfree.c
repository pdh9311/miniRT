#include "list.h"

void		free_lst(t_lst *lst)
{
	t_lst	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}
