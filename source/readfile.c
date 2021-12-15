#include "libft.h"
#include "utils.h"
#include "element.h"

int	check_type(char **split, char *type, t_lst **lst)
{
	static const int	total = 6;
	static const char	*type_str[] = {
		"A", "C", "L", "pl", "sp", "cy"
	};
	static	int			(*type_func[])(char **, t_lst **) = {
		&input_type_a, &input_type_c,
		&input_type_l, &input_type_pl,
		&input_type_sp, &input_type_cy
	};
	int					idx;

	idx = -1;
	while (++idx < total)
		if (ft_strcmp(type_str[idx], type) == 0)
			break ;
	printf("%s\n", type);
	if (idx == total)
	{
		ft_putendl_fd("Error\n  Wrong type", 2);
		return (EXIT_FAILURE);
	}
	if (type_func[idx](split, lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
		return (EXIT_FAILURE);
	if (check_type(split, split[0], lst) == EXIT_FAILURE)
		return (free_dptr(split, EXIT_FAILURE));
	return (free_dptr(split, EXIT_SUCCESS));
}

int	check_camera(t_lst *lst)
{
	int	cnt;

	cnt = 0;
	while (lst != NULL)
	{
		if (((t_element *)(lst->content))->type == 1)
			cnt++;
		lst = lst->next;
	}
	if (cnt == 0)
	{
		ft_putendl_fd("Error\n  Not found camera", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
		if (ft_strcmp(line, "") == 0)
			continue ;
		printf("line: %s\n", line);
		if (line_split(line, lst))
		{
			free_ptr(line, 0);
			if (*lst != NULL)
				free_lst(*lst);
			close(fd);
			return (EXIT_FAILURE);
		}
		free_ptr(line, 0);
	}
	close(fd);
	return (check_camera(*lst));
}
