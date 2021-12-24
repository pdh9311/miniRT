/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:54:41 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:54:41 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
