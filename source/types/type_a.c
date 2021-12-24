/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:32 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:33 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"
#include "libft.h"

int	input_type_a(char **split, t_lst **lst)
{
	t_element	*elem;

	if (split_cnt(split) != 3)
	{
		ft_putendl_fd("Error\n  Wrong argument count a", 2);
		return (EXIT_FAILURE);
	}
	elem = (t_element *)malloc(sizeof(t_element));
	if (elem == NULL)
		return (EXIT_FAILURE);
	ft_memset(elem, 0, sizeof(t_element));
	elem->coord = (t_point3){0, 0, 0};
	elem->brightness = ft_atof(split[1]);
	elem->rgb = get_color(split[2]);
	elem->type = A;
	if (check_ratio(elem->brightness) || check_rgb(elem->rgb))
	{
		free(elem);
		ft_putendl_fd("Error\n  Not in range", 2);
		return (EXIT_FAILURE);
	}
	pp_lstadd_back(lst, pp_lstnew(elem));
	return (EXIT_SUCCESS);
}
