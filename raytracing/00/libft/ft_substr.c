/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:14:43 by donpark           #+#    #+#             */
/*   Updated: 2021/11/22 17:14:41 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		substr = (char *)ft_calloc(1, sizeof(char));
		if (substr == NULL)
			return (0);
		return (substr);
	}
	substr = (char *)ft_calloc(len + 1, sizeof(char));
	if (substr == NULL)
		return (0);
	i = 0;
	while (s[i] && i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
