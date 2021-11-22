#include "miniRT.h"
#include "libft.h"
#include "element.h"

int	free_dptr(char **dptr, int ret)
{
	int	i;

	i = 0;
	while (dptr[i] != NULL)
	{
		free(dptr[i]);
		dptr[i] = NULL;
		i++;
	}
	if (dptr != NULL)
	{
		free(dptr);
		dptr = NULL;
	}
	return (ret);
}

void	print_str_arr(char **str_arr)
{	
	int	i;

	i = 0;
	while (str_arr[i])
	{
		printf("%s\t", str_arr[i]);
		i++;
	}
	printf("\n");
}

t_color	set_color(char *rgb)
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

int	input_type_a(char **split)
{
	t_element	*elem;

	elem = (t_element *)malloc(sizeof(t_element));
	if (elem == NULL)
		return (EXIT_FAILURE);
	ft_memset(elem, 0, sizeof(t_element));
	elem->brightness = ft_atof(split[1]);
	elem->rgb = set_color(split[2]);
	// lst에 추가
	printf("%lf, %d %d %d\n", elem->brightness, elem->rgb.r, elem->rgb.g, elem->rgb.b);
	return (EXIT_SUCCESS);	
}

t_coord	set_coord(char *data)
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



int	input_type_c(char **split)
{
	t_element	*elem;

	elem = (t_element *)malloc(sizeof(t_element));
	if (elem == NULL)
		return (EXIT_FAILURE);
	ft_memset(elem, 0, sizeof(t_element));
	elem->coord = set_coord(split[1]);
	elem->vector = set_coord(split[2]);
	elem->fov = ft_atof(split[3]);
	// lst에 추가
	printf("%lf,%lf,%lf | %lf,%lf,%lf, | %lf\n", elem->coord.x, elem->coord.y, elem->coord.z,\
		elem->vector.x, elem->vector.y, elem->vector.z, elem->fov);
	return (EXIT_SUCCESS);	
}	

int	check_type(char **split, char *type)
{
	if (ft_strcmp(type, "A") == 0)
	{
		if (input_type_a(split))
			return (free_dptr(split, EXIT_FAILURE));
	}
	else if (ft_strcmp(type, "C") == 0)
	{
		if (input_type_c(split))
			return (free_dptr(split, EXIT_FAILURE));
	}
	else if (ft_strcmp(type, "L") == 0)
	{
		
	}
	else if (ft_strcmp(type, "pl") == 0)
	{

	}
	else if (ft_strcmp(type, "sp") == 0)
	{

	}
	else if (ft_strcmp(type, "cy") == 0)
	{

	}
	return (EXIT_SUCCESS);
}

int	readfile(char *file)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_multi_split(line, " \r\t\v\f\n");
		check_type(split, split[0]);
		// print_str_arr(split);




		free(line);		
	}

	close(fd);
	return (EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{

	if (argc != 2)
		return (EXIT_FAILURE);
    readfile(argv[1]);
	return (EXIT_SUCCESS);
}