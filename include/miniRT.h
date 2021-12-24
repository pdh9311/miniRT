/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:58:23 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:58:23 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include "camera.h"
# include "mlx.h"
# include "ray.h"
# include "sphere.h"
# include "plane.h"
# include "cylinder.h"
# include "hit.h"
# include "list.h"
# include "element.h"
# include "libft.h"

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			size_l;
	int			endian;
	t_color		pixel_color;
	int			rgb[3];
	int			color;
}				t_mlx;

typedef struct s_light
{
	t_point3	origin;
	t_color		color;
	float		bright_ratio;
}				t_light;

typedef struct s_scene
{
	t_mlx		mlx;
	t_lst		*cam_list;
	t_lst		*cam_list_move;
	t_camera	*camera;
	t_ray		ray;
	t_hlist		*list;
	t_light		*light;
	t_lst		*light_list;
	t_lst		*light_list_move;
	t_light		ambient;
}				t_scene;

typedef struct s_phong
{
	t_vec3			light_dir;
	t_vec3			light_unit_dir;
	float			kd;
	t_ray			light_ray;
	float			light_len;
	t_hit_record	shadow_rec;
	t_color			specular;
	float			ksn;
	float			ks;
	t_vec3			view_dir;
	t_vec3			reflect_dir;
	float			spec;
}				t_phong;

// readfile.c
int		readfile(char *file, t_lst **lst);

// init.c
void	init(t_scene *scene, t_lst *lst);

// camera_init.c
int		make_cam_list(t_scene *scene, t_element *elem);
void	init_camera(t_camera *cam, t_element *elem);
void	set_camera(t_scene *scene);

// camear_util.c
void	next_camera(t_scene *scene);
void	previous_camera(t_scene *scene);
int		free_cameras(t_lst *cam_list);

// light_init.c
void	init_light(t_light *light, t_element *elem);
void	set_light(t_scene *scene);
int		make_light_list(t_scene *scene, t_element *elem);
void	next_light(t_scene *scene);
void	previous_light(t_scene *scene);

// random_clamp.c
float	deg_to_rad(float degrees);
float	random_float(void);
float	random_float_(float min, float max);
float	clamp(float x, float min, float max);

// ambient.c
void	set_ambient(t_color *pixel_color, t_scene *scene, t_hit_record *rec);

// diffuse.c
void	set_diffuse(t_color *pixel_color, t_scene *scene, \
					t_hit_record *rec, t_phong *phong);

// shadow.c
int		set_shadow(t_scene *scene, t_hit_record *rec, t_phong *phong);

// specular.c
void	set_specular(t_color *pixel_color, t_scene *scene, \
					t_hit_record *rec, t_phong *phong);

void	print_lst(t_lst *lst);
#endif
