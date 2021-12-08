#ifndef HIT_H
# define HIT_H

# include "vec3.h"
# include "ray.h"

# define TMIN 0.0001
# define TMAX 3.40282347E+38

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		t;
	t_color		albedo;
}				t_hit_record;

typedef enum e_type
{
	_none,
	_sphere
}				t_type;

typedef struct s_object
{
	t_type	type;
	t_color	albedo;
	void	*figure;
}				t_object;

typedef struct s_hlist
{
	t_object		object;
	struct s_hlist	*next;
}					t_hlist;

void	init_hit_record(t_hit_record *rec);
int		hit(t_hlist *current, t_ray *r, t_hit_record *rec, double max);

t_hlist	*list_(t_object object);
void	push(t_hlist **lst, t_hlist *new_node);
void	clear(t_hlist **lst);


#endif