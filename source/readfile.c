#include "element.h"
#include "libft.h"

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
		if (input_type_l(split))
			return (free_dptr(split, EXIT_FAILURE));
		
	}
	else if (ft_strcmp(type, "pl") == 0)
	{
		if (input_type_pl(split))
			return (free_dptr(split, EXIT_FAILURE));

	}
	else if (ft_strcmp(type, "sp") == 0)
	{
		if (input_type_sp(split))
			return (free_dptr(split, EXIT_FAILURE));

	}
	else if (ft_strcmp(type, "cy") == 0)
	{
		if (input_type_cy(split))
			return (free_dptr(split, EXIT_FAILURE));

	}
	return (EXIT_SUCCESS);
}

int	readfile(char *file)
{
	int		fd;
	char	*line;
	char	**split;
	int		gnl_ret;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	while (1)
	{
		gnl_ret = get_next_line(fd, &line);
		split = ft_multi_split(line, " \r\t\v\f\n");
		check_type(split, split[0]);
		// print_str_arr(split);
		free(line);
		if (gnl_ret <= 0)
			break ;
	}
	close(fd);
	return (EXIT_SUCCESS);
}