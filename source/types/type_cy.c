/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_cy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:35 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:36 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"
#include "libft.h"

static int	cy_split_cnt(char **split)
{
	if (split_cnt(split) != 6)
	{
		ft_putendl_fd("Error\n  Wrong argument count cy", 2);
		return (FALSE);
	}
	return (TRUE);
}

int	input_type_cy(char **split, t_lst **lst)
{
	t_element	*elem;

	if (cy_split_cnt(split) == FALSE)
		return (EXIT_FAILURE);
	elem = (t_element *)malloc(sizeof(t_element));
	if (elem == NULL)
		return (EXIT_FAILURE);
	ft_memset(elem, 0, sizeof(t_element));
	elem->coord = get_point3(split[1]);
	elem->vector = get_point3(split[2]);
	elem->diameter = ft_atof(split[3]);
	elem->height = ft_atof(split[4]);
	elem->rgb = get_color(split[5]);
	elem->type = CY;
	if (check_axis(elem->vector) || check_rgb(elem->rgb) \
		|| elem->diameter < 0 || elem->height < 0)
	{
		free(elem);
		ft_putendl_fd("Error\n  Not in range", 2);
		return (EXIT_FAILURE);
	}
	pp_lstadd_back(lst, pp_lstnew(elem));
	return (EXIT_SUCCESS);
}
