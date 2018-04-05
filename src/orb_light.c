/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orb_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 14:32:44 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/31 12:03:46 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		is_in_orb_light(t_light *light, t_ray *light_ray)
{
	(void)light;
	(void)light_ray;
	return (1);
}

static t_vector	get_orb_ray_vect(t_dot pos, t_light *light)
{
	return ((t_vector){((t_orb_light*)light)->orig.x - pos.x,
						((t_orb_light*)light)->orig.y - pos.y,
						((t_orb_light*)light)->orig.z - pos.z});
}

t_orb_light		*new_orb_light(t_dot orig, SDL_Color color, double power)
{
	t_orb_light	*orb;

	orb = (t_orb_light*)new_spotlight((t_light_crd){orig, (t_vector){0, 0, 0}},
									color, 360, power);
	orb->is_in_light = &is_in_orb_light;
	orb->get_ray_vect = &get_orb_ray_vect;
	return (orb);
}

void			delete_orb_light(t_orb_light *orb)
{
	delete_spotlight((t_spotlight*)orb);
}
