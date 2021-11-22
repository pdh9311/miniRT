/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_wordcnt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:58:59 by joonpark          #+#    #+#             */
/*   Updated: 2021/11/22 16:03:19 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_str(char const *s, char c)
{
	int	idx;

	idx = 0;
	while (s[idx])
	{
		if (s[idx] == c)
			return (1);
		++idx;
	}
	return (0);
}

size_t	ft_multi_wordcnt(char const *s, char *delimeter)
{
	size_t	cnt;
	size_t	i;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (is_in_str(delimeter, s[i]) == 0)
		{
			cnt++;
			while (s[i] && is_in_str(delimeter, s[i]) == 0)
				i++;
		}
		else
			i++;
	}
	return (cnt);
}
