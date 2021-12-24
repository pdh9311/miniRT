/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:58:21 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:58:22 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef struct s_lst
{
	void			*content;
	struct s_lst	*prev;
	struct s_lst	*next;
}	t_lst;

t_lst	*pp_lstnew(void *content);
int		pp_lstsize(t_lst *lst);
t_lst	*pp_lstlast(t_lst *lst);
void	pp_lstadd_back(t_lst **lst, t_lst *new);
void	pp_lstadd_front(t_lst **lst, t_lst *new);
void	pp_lstdelone(t_lst *lst);
void	free_lst(t_lst *lst);

#endif
