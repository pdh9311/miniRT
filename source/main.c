/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:57:48 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 16:02:52 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "list.h"
#include "keyhook.h"

/**
 * pixel_color = (t_color){0, 0, 0};
 */
t_color	ray_color(t_scene *scene)
{
	t_color			pixel_color;
	t_hit_record	rec;
	float			t;
	t_phong			phong;
	int				flag;

	flag = 0;
	init_hit_record(&rec);
	if (hit(scene->list, &scene->ray, &rec, TMAX))
	{
		pixel_color = (t_color){0.0, 0.0, 0.0};
		set_diffuse(&pixel_color, scene, &rec, &phong);
		if (set_shadow(scene, &rec, &phong))
			flag = 1;
		set_specular(&pixel_color, scene, &rec, &phong);
		set_ambient(&pixel_color, scene, &rec);
		if (flag == 1)
			return (multiply(pixel_color, 0.7));
		return (pixel_color);
	}
	t = fabs((scene->ray.direction.y + 1) * 0.5);
	pixel_color = add(multiply(color_(1.0, 1.0, 1.0), 1 - t), \
						multiply(color_(0.5, 0.7, 1.0), t));
	return (pixel_color);
}

int	draw(void *param)
{
	t_scene		*scene;
	double		u;
	double		v;
	int			y;
	int			x;

	scene = param;
	y = scene->camera->image_height;
	while (--y >= 0)
	{
		x = -1;
		while (++x < scene->camera->image_width)
		{
			u = (double)x / scene->camera->image_width;
			v = (double)(scene->camera->image_height - 1 - y) \
				/ scene->camera->image_height;
			scene->ray = ray_(scene->camera->origin, \
							new_ray_dir(scene->camera, u, v));
			scene->mlx.pixel_color = ray_color(scene);
			write_color(scene, y, x);
		}
	}
	mlx_put_image_to_window(scene->mlx.mlx_ptr, \
			scene->mlx.win_ptr, scene->mlx.img_ptr, 0, 0);
	return (TRUE);
}

/**
 * // mlx_hook(mlx->win_ptr, BTN_PRESS, 1L << 2, mouse_hook, &scene);
 */
int	main(int argc, char *argv[])
{
	t_scene		scene;
	t_mlx		*mlx;
	t_lst		*lst;

	if (argc != 2)
	{
		ft_putendl_fd("Error\n  Wrong argument count", 2);
		return (EXIT_FAILURE);
	}
	mlx = &scene.mlx;
	lst = NULL;
	if (readfile(argv[1], &lst))
		return (EXIT_FAILURE);
	init(&scene, lst);
	mlx_hook(mlx->win_ptr, KEY_PRESS, 1L << 0, key_hook, &scene);
	mlx_hook(mlx->win_ptr, DESTROY, 0, close_screen, &scene);
	mlx_loop_hook(mlx->mlx_ptr, &draw, &scene);
	mlx_loop(mlx->mlx_ptr);
	return (EXIT_SUCCESS);
}
