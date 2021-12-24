/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:56:43 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:56:44 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

static void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->size_l + x * (mlx->bpp / 8));
	*((unsigned int *)dst) = color;
}

void	write_color(t_scene *scene, int y, int x)
{
	t_mlx	*mlx;

	mlx = &scene->mlx;
	mlx->rgb[0] = (int)(mlx->pixel_color.x * 255.);
	mlx->rgb[1] = (int)(mlx->pixel_color.y * 255.);
	mlx->rgb[2] = (int)(mlx->pixel_color.z * 255.);
	mlx->color = mlx->rgb[0] << 16 | mlx->rgb[1] << 8 | mlx->rgb[2];
	my_mlx_pixel_put(&scene->mlx, x, y, mlx->color);
}
