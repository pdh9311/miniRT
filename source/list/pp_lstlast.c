/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:54:48 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:54:48 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_lst	*pp_lstlast(t_lst *lst)
{
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
