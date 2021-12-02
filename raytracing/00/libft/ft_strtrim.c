/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 03:55:03 by donpark           #+#    #+#             */
/*   Updated: 2021/11/22 17:14:41 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*strtrim;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (0);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]) != 0)
		start++;
	if (start >= ft_strlen(s1))
	{
		strtrim = (char *)ft_calloc(1, sizeof(char));
		if (strtrim == NULL)
			return (0);
		return (strtrim);
	}
	while (end > 0 && ft_strchr(set, s1[end]) != 0)
		end--;
	strtrim = ft_substr(s1, start, (end - start + 1));
	return (strtrim);
}
