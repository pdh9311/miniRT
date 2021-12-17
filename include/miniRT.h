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
	t_camera	camera;
	t_ray		ray;
	t_hlist		*list;
	//t_object	*lights;
	t_light		light;
	t_light		ambient; // Ambient
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

// random_clamp.c
float	deg_to_rad(float degrees);
float	random_float(void);
float	random_float_(float min, float max);
float	clamp(float x, float min, float max);

// ambient.c
void	set_ambient(t_color *pixel_color, t_scene *scene, t_hit_record *rec);
// diffuse.c
void	set_diffuse(t_color *pixel_color, t_scene *scene, t_hit_record *rec, t_phong *phong);
// shadow.c
int		set_shadow(t_scene *scene, t_hit_record *rec, t_phong *phong);
// specular.c
void	set_specular(t_color *pixel_color, t_scene *scene, t_hit_record *rec, t_phong *phong);

void	print_lst(t_lst *lst);
#endif
