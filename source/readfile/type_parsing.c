#include "utils.h"
#include "element.h"

int	check_type(char **split, char *type, t_lst **lst)
{
	static const int	total = 7;					/// MOD: 6 -> 7
	static const char	*type_str[] = {
		"A", "C", "L", "pl", "sp", "cy", "co"		/// ADD: "co"
	};
	static	int			(*type_func[])(char **, t_lst **) = {
		&input_type_a, &input_type_c,
		&input_type_l, &input_type_pl,
		&input_type_sp, &input_type_cy,
		&input_type_co								/// ADD: &input_type_co
	};
	int					idx;

	idx = -1;
	while (++idx < total)
		if (ft_strcmp(type_str[idx], type) == 0)
			break ;
	if (idx == total)
	{
		ft_putendl_fd("Error\n  Wrong type", 2);
		return (EXIT_FAILURE);
	}
	if (type_func[idx](split, lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	line_split(char *line, t_lst **lst)
{
	char	**split;

	split = ft_multi_split(line, " \r\t\v\f\n");
	if (split == NULL)
		return (EXIT_FAILURE);
	if (check_type(split, split[0], lst) == EXIT_FAILURE)
		return (free_dptr(split, EXIT_FAILURE));
	return (free_dptr(split, EXIT_SUCCESS));
}
