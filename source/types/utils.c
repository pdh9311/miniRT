#include "element.h"
#include "libft.h"
#include "utils.h"
#include <stdio.h> //

t_color	get_color(char *rgb)
{
	t_color	color;
	char	**rgb_split;

	rgb_split = ft_split(rgb, ',');
	color.r = ft_atoi(rgb_split[0]);
	color.g = ft_atoi(rgb_split[1]);
	color.b = ft_atoi(rgb_split[2]);
	free_dptr(rgb_split, 0);
	return (color);
}

t_coord	get_coord(char *data)
{
	t_coord	coord;
	char	**data_split;

	data_split = ft_split(data, ',');
	coord.x = ft_atof(data_split[0]);
	coord.y = ft_atof(data_split[1]);
	coord.z = ft_atof(data_split[2]);
	free_dptr(data_split, 0);
	return (coord);
}
