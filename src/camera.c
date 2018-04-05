/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 13:12:56 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/22 11:14:48 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_camera	new_camera(const t_dot origin, const t_dot angle,
					double field_of_view, double depth_of_field)
{
	t_camera	cam;

	cam.origin = origin;
	cam.angle = angle;
	cam.focal = get_sdl_core()->width / (2 * tan((field_of_view * M_PI / 180) /
				2.0f));
	ft_putstr("Focal dist: ");
	ft_putnbr(cam.focal);
	ft_putchar('\n');
	cam.depth = depth_of_field;
	cam.vp.front = vector(1, 0, 0);
	cam.vp.up = vector(0, 1, 0);
	cam.vp.right = vector(0, 0, 1);
	cam.fov = field_of_view;
	return (cam);
}

void		reset_camera(t_camera *cam)
{
	cam->focal = get_sdl_core()->width / (2 * tan((cam->fov * M_PI / 180) /
				2.0f));
	ft_putstr("Focal dist: ");
	ft_putnbr(cam->focal);
	ft_putchar('\n');
	cam->vp.front = vector(1, 0, 0);
	cam->vp.up = vector(0, 1, 0);
	cam->vp.right = vector(0, 0, 1);
}
