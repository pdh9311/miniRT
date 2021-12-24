/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:27 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:57:27 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "element.h"

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

static void	check_cam_light_helper(t_lst *lst, int *cam_cnt, int *light_cnt)
{
	*cam_cnt = 0;
	*light_cnt = 0;
	while (lst != NULL)
	{
		if (((t_element *)(lst->content))->type == C)
			(*cam_cnt)++;
		if (((t_element *)(lst->content))->type == L)
			(*light_cnt)++;
		lst = lst->next;
	}
}

static int	check_cam_light(t_lst *lst)
{
	int	cam_cnt;
	int	light_cnt;

	check_cam_light_helper(lst, &cam_cnt, &light_cnt);
	if (cam_cnt < 1)
	{
		ft_putendl_fd("Error\n  Not found camera", 2);
		free_lst(lst);
		return (EXIT_FAILURE);
	}
	if (light_cnt > 100)
	{
		ft_putendl_fd("Error\n  Wrong light count", 2);
		free_lst(lst);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	read_and_parsing(t_rdfile *rd, t_lst **lst)
{
	while (rd->flag)
	{
		if (read_line(rd->fd, &rd->line, &rd->flag))
			break ;
		if (ft_strcmp(rd->line, "") == 0)
		{
			free_ptr(rd->line, 0);
			continue ;
		}
		if (line_split(rd->line, lst))
		{
			free_ptr(rd->line, 0);
			if (*lst != NULL)
				free_lst(*lst);
			close(rd->fd);
			return (EXIT_FAILURE);
		}
		free_ptr(rd->line, 0);
	}
	return (EXIT_SUCCESS);
}

int	readfile(char *file, t_lst **lst)
{
	t_rdfile	rd;
	char		*check;

	check = ft_strrchr(file, '.');
	if (ft_strcmp(".rt", check) != 0)
	{
		ft_putendl_fd("Error\n  Wrong file type", 2);
		return (EXIT_FAILURE);
	}
	rd.fd = open(file, O_RDONLY);
	if (rd.fd < 0)
	{
		ft_putendl_fd("Error\n  Not found file open", 2);
		return (EXIT_FAILURE);
	}
	rd.flag = 1;
	if (read_and_parsing(&rd, lst))
		return (EXIT_FAILURE);
	close(rd.fd);
	return (check_cam_light(*lst));
}
