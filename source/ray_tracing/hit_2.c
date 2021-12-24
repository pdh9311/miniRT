/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:56:55 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:56:55 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

t_hlist	*list_(t_object object)
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

void	clear(t_hlist **lst)
{
	t_hlist	*temp;

	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			if (*lst)
			{
				free((*lst)->object.figure);
				free(*lst);
			}
			(*lst) = temp;
		}
		lst = NULL;
	}
}
