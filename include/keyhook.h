/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:58:12 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:58:13 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYHOOK_H
# define KEYHOOK_H

# include "keycode.h"
# include "miniRT.h"

# define KEY_PRESS		2
# define KEY_RELEASE	3
# define BTN_PRESS		4
# define BTN_RELEASE	5
# define MOUSE_MOVE		6
# define DESTROY		17

int		key_hook(int keycode, t_scene *scene);
int		close_screen(void *param);
void	camera_move(t_camera *cam, int keycode);
void	camera_rotate(t_camera *cam, int keycode);
void	camera_change(t_scene *scene, int keycode);
void	light_change(t_scene *scene, int keycode);

#endif
