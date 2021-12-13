#ifndef ELEMENT_H
# define ELEMENT_H

# include "list.h"
# include "vec3.h"

enum	e_type_str
{
	A = 0,
	C,
	L,
	PL,
	SP,
	CY
};

typedef struct s_check
{
	int			coord;
	int			vector;
	int			rgb;
	int			brightness;
	int			diameter;
	int			height;
	int			fov;
}				t_check;

typedef struct s_element
{
	t_check		check;
	t_point3	coord;
	t_vec3		vector;
	t_color		rgb;
	double		brightness;
	double		diameter;
	double		height;
	double		fov;
	int			type;
}				t_element;

int			readfile(char *file, t_lst **lst);

int			input_type_a(char **split, t_lst **lst);
int			input_type_c(char **split, t_lst **lst);
int			input_type_l(char **split, t_lst **lst);
int			input_type_pl(char **split, t_lst **lst);
int			input_type_sp(char **split, t_lst **lst);
int			input_type_cy(char **split, t_lst **lst);
t_color		get_color(char *rgb);
t_point3	get_point3(char *data);

#endif