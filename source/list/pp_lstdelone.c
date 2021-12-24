/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:54:43 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:54:44 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
