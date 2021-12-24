/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:54:50 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:54:51 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "libft.h"

t_lst	*pp_lstnew(void *content)
{
	t_lst	*node;

	node = (t_lst *)malloc(sizeof(t_lst));
	if (node == NULL)
		return (0);
	ft_memset(node, 0, sizeof(t_lst));
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
