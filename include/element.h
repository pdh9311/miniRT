#ifndef ELEMENT_H
# define ELEMENT_H

# include "list.h"

enum e_type
{
	A = 0,
	C,
	L,
	PL,
	SP,
	CY
};

typedef struct s_coord
{
	double		x;
	double		y;
	double		z;
}				t_coord;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

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
	t_coord		coord;
	t_coord		vector;
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
t_coord		get_coord(char *data);

#endif