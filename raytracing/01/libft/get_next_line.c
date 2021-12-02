/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 03:26:41 by donpark           #+#    #+#             */
/*   Updated: 2021/07/07 18:56:48 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_memory_free(void **m)
{
	if (*m)
	{
		free(*m);
		*m = 0;
		return (1);
	}
	return (0);
}

int	is_newline(char *backup)
{
	int	i;

	i = 0;
	while (backup[i])
	{
		if (backup[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	split_line(char **backup, char **line, int cut_idx, char *buf)
{
	char	*tmp;
	int		len;

	gnl_memory_free((void **)&buf);
	(*backup)[cut_idx] = '\0';
	*line = ft_strdup(*backup);
	if (*line == NULL)
		return (-1);
	len = ft_strlen(*backup + cut_idx + 1);
	if (len == 0)
	{
		gnl_memory_free((void **)backup);
		return (1);
	}
	tmp = ft_strdup(*backup + cut_idx + 1);
	if (tmp == NULL)
		return (-1);
	gnl_memory_free((void **)backup);
	*backup = tmp;
	return (1);
}

int	remains_data(char **backup, char **line, int read_size, char *buf)
{
	int	cut_idx;

	gnl_memory_free((void **)&buf);
	if (read_size < 0)
	{
		gnl_memory_free((void **)backup);
		return (-1);
	}
	if (*backup && is_cut_idx(*backup, &cut_idx))
		return (split_line(backup, line, cut_idx, buf));
	if (*backup)
	{
		*line = *backup;
		*backup = 0;
	}
	else
	{
		*line = ft_strdup("");
		if (*line == NULL)
			return (-1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int			read_size;
	char		*buf;
	static char	*backup[OPEN_MAX + 1];
	int			cut_idx;
	char		*tmp;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX || !line)
		return (-1);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (-1);
	while (is_read_size(&read_size, fd, &buf))
	{
		buf[read_size] = '\0';
		tmp = ft_strjoin(backup[fd], buf);
		if (tmp == NULL)
			return (-1);
		gnl_memory_free((void **)&backup[fd]);
		backup[fd] = tmp;
		if (is_cut_idx(backup[fd], &cut_idx))
			return (split_line(&backup[fd], line, cut_idx, buf));
	}
	return (remains_data(&backup[fd], line, read_size, buf));
}
