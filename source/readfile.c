#include "libft.h"
#include "utils.h"
#include "element.h"

int	check_type(char **split, char *type, t_lst **lst)
{
	static const int	total = 6;
	static const char	*type_str[] = {
		"A", "C", "L", "pl", "sp", "cy", NULL
	};
	static		int		(*type_func[])(char **, t_lst **) = {
		&input_type_a, &input_type_c,
		&input_type_l, &input_type_pl,
		&input_type_sp, &input_type_cy
	};
	int					idx;

	idx = -1;
	while (++idx <= total)
	{
		if (ft_strcmp(type_str[idx], type) == 0)
			break ;
	}
	if (idx <= total)
	{
		if (idx < total && type_func[idx](split, lst) == EXIT_FAILURE)
			return (free_dptr(split, EXIT_FAILURE));
		else
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static int	read_line(int fd, char **line, int *flag)
{
	int	gnl_ret;

	gnl_ret = get_next_line(fd, line);
	if (gnl_ret < 0)
		return (EXIT_FAILURE);
	if (gnl_ret == 0)
		*flag = 0;
	return (EXIT_SUCCESS);
}

static int	line_split(char *line, t_lst **lst)
{
	char	**split;

	split = ft_multi_split(line, " \r\t\v\f\n");
	if (split == NULL)
	{
		free_ptr(line, 0);
		return (EXIT_FAILURE);
	}
	if (check_type(split, split[0], lst) == EXIT_FAILURE)
	{
		free_ptr(line, 0);
		return (free_dptr(split, EXIT_FAILURE));
	}
	return (free_dptr(split, EXIT_SUCCESS));
}

int	readfile(char *file, t_lst **lst)
{
	int		fd;
	char	*line;
	int		flag;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	flag = 1;
	while (flag)
	{
		if (read_line(fd, &line, &flag))
			break ;
		if (line_split(line, lst))
			break ;
		// print_str_arr(split);
		free_ptr(line, 0);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
