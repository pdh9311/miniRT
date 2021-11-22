#ifndef ELEMENT_H
# define ELEMENT_H

typedef struct	s_coord
{
	double		x;
	double		y;
	double		z;
}				t_coord;

typedef struct	s_color
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

typedef struct  s_element
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

#endif