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

#endif