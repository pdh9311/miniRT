/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:58:04 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:58:05 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H

# include "list.h"
# include "vec3.h"
# include "libft.h"

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
	float		brightness;
	float		diameter;
	float		height;
	float		fov;
	int			type;
}				t_element;

typedef struct s_rdfile
{
	int			fd;
	char		*line;
	int			flag;
}				t_rdfile;

int			readfile(char *file, t_lst **lst);

int			line_split(char *line, t_lst **lst);
int			check_type(char **split, char *type, t_lst **lst);

int			input_type_a(char **split, t_lst **lst);
int			input_type_c(char **split, t_lst **lst);
int			input_type_l(char **split, t_lst **lst);
int			input_type_pl(char **split, t_lst **lst);
int			input_type_sp(char **split, t_lst **lst);
int			input_type_cy(char **split, t_lst **lst);
t_color		get_color(char *rgb);
t_point3	get_point3(char *data);
int			split_cnt(char **split);

int			check_rgb(t_color rgb);
int			check_ratio(float ratio);
int			check_axis(t_vec3 axis);
int			check_fov(float fov);

#endif
