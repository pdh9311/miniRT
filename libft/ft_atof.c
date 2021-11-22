/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:09:07 by joonpark          #+#    #+#             */
/*   Updated: 2021/11/22 17:53:15 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static double	ft_pow(int i)
{
	double	ret;

	ret = 1.0;
	while (i > 0)
	{
		ret /= 10.0;
		--i;
	}
	return (ret);
}

double	ft_atof(const char *str)
{	
	double	ret;
	int		idx;
	int		minus;

	ret = 0.;
	minus = 1;
	if (*str && *str == '-')
	{
		minus = -1;
		++str;
	}
	while (*str && (*str >= '0' && *str <= '9'))
		ret = (ret * 10.) + (*(str++) - '0');
	if (*(str++) != '.')
		return (ret);
	idx = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		ret = (ret * 10.) + (*str - '0');
		++str;
		++idx;
	}
	return (ret * minus * ft_pow(idx));
}
