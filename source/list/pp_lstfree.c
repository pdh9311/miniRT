/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:54:46 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:54:46 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	free_lst(t_lst *lst)
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
