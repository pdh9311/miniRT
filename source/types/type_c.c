/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:34 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:34 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"
#include "libft.h"

int	input_type_c(char **split, t_lst **lst)
{
	t_element	*elem;

	if (split_cnt(split) != 4)
	{
		ft_putendl_fd("Error\n  Wrong argument count c", 2);
		return (EXIT_FAILURE);
	}
	elem = (t_element *)malloc(sizeof(t_element));
	if (elem == NULL)
		return (EXIT_FAILURE);
	ft_memset(elem, 0, sizeof(t_element));
	elem->coord = get_point3(split[1]);
	elem->vector = get_point3(split[2]);
	elem->fov = ft_atof(split[3]);
	elem->type = C;
	if (check_axis(elem->vector) || check_fov(elem->fov))
	{
		free(elem);
		ft_putendl_fd("Error\n  Not in range", 2);
		return (EXIT_FAILURE);
	}
	pp_lstadd_back(lst, pp_lstnew(elem));
	return (EXIT_SUCCESS);
}
