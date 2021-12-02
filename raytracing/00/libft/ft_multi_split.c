/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 04:31:31 by donpark           #+#    #+#             */
/*   Updated: 2021/11/22 17:14:41 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_worddup(const char *s, char *delimeter)
{
	char	*word;
	size_t	w_len;

	w_len = 0;
	while (s[w_len] && is_in_str(delimeter, s[w_len]) == 0)
		w_len++;
	word = (char *)ft_calloc(w_len + 1, sizeof(char));
	if (word == NULL)
		return (0);
	ft_strlcpy(word, s, w_len + 1);
	return (word);
}

static char	**ft_freeall(char **dptr)
{
	size_t	i;

	i = 0;
	while (dptr[i] != 0)
	{
		free(dptr[i]);
		i++;
	}
	free(dptr);
	return (0);
}

static int	ft_input_word(const char *s, char *delimeter, \
	char **words, size_t w_cnt)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < w_cnt && s[j])
	{
		if (is_in_str(delimeter, s[j]) == 0)
		{
			words[i++] = ft_worddup(&s[j], delimeter);
			if (words[i - 1] == NULL)
			{
				ft_freeall(words);
				return (-1);
			}
			while (s[j] && is_in_str(delimeter, s[j]) == 0)
				j++;
		}
		else
			j++;
	}
	return (i);
}

char	**ft_multi_split(const char *s, char *delimeter)
{
	char	**words;
	size_t	w_cnt;

	if (!s)
		return (0);
	w_cnt = ft_multi_wordcnt(s, delimeter);
	words = (char **)ft_calloc(w_cnt + 1, sizeof(char *));
	if (words == NULL)
		return (0);
	if (ft_input_word(s, delimeter, words, w_cnt) == -1)
		return (0);
	return (words);
}
