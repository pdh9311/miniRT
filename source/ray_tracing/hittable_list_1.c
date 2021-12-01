#include "hittable_list.h"

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