#include "element.h"
#include "libft.h"
#include "utils.h"

t_color	get_color(char *rgb)
{
	t_color	color;
	char	**rgb_split;

	rgb_split = ft_split(rgb, ',');
	color.x = ft_atoi(rgb_split[0]);
	color.y = ft_atoi(rgb_split[1]);
	color.z = ft_atoi(rgb_split[2]);
	free_dptr(rgb_split, 0);
	return (color);
}

t_point3	get_point3(char *data)
{
	t_point3	coord;
	char		**data_split;

	data_split = ft_split(data, ',');
	if (data_split[0] == NULL)
		coord.x = 0;
	else
		coord.x = ft_atof(data_split[0]);
	if (data_split[1] == NULL)
		coord.y = 0;
	else
		coord.y = ft_atof(data_split[1]);
	if (data_split[2] == NULL)
		coord.z = 0;
	else
		coord.z = ft_atof(data_split[2]);
	free_dptr(data_split, 0);
	return (coord);
}

int	split_cnt(char **split)
{
	int	cnt;

	cnt = 0;
	if (split == NULL)
		return (0);
	while (split[cnt])
		cnt++;
	return (cnt);
}
