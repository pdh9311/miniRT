#ifndef HITTABLE_LIST_H
# define HITTABLE_LIST_H

# include "hittable.h"
# include "sphere.h"

typedef struct s_hlist
{
	t_hittable	object;
	struct list	*next;
}	t_hlist;

t_hlist	*list_(t_hittable object);
void	push(t_hlist **lst, t_hlist *new);
void	drop(t_hlist *lst);
void	clear(t_hlist **lst);
int		hit_(t_hittable *object, t_ray *r, double t_min, double t_max, t_hit_record *rec);
int		hit(t_hlist *current, t_ray *r, double t_min, double t_max, t_hit_record *rec);
#endif
