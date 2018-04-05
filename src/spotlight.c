/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 14:04:25 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/19 18:42:34 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		is_in_spotlight(t_light *light, t_ray *light_ray)
{
	t_vector	opposite;
	t_spotlight	*s;

	s = (t_spotlight*)light;
	opposite = (t_vector){-s->direction.x, -s->direction.y, -s->direction.z};
	if (angle_between_vectors(light_ray->equ.vd, opposite) > s->aperture)
		return (0);
	return (1);
}

static t_vector	get_spot_ray_vect(t_dot pos, t_light *light)
{
	return ((t_vector){((t_spotlight*)light)->orig.x - pos.x,
						((t_spotlight*)light)->orig.y - pos.y,
						((t_spotlight*)light)->orig.z - pos.z});
}

t_spotlight		*new_spotlight(t_light_crd coords, SDL_Color color,
								double aperture, double power)
{
	t_spotlight	*spot;

	if (aperture == 360)
		spot = (t_spotlight*)new_light(ORB, coords.direction, color, power);
	else
		spot = (t_spotlight*)new_light(SPOT, coords.direction, color, power);
	spot->orig = coords.orig;
	spot->aperture = aperture;
	spot->get_ray_vect = &get_spot_ray_vect;
	spot->is_in_light = &is_in_spotlight;
	return (spot);
}

void			delete_spotlight(t_spotlight *spot)
{
	delete_light((t_light*)spot);
}
