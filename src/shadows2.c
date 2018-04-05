/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 11:22:51 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/19 18:47:41 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			check_objs_on_ray(t_ray *light_ray, const t_list_objs *l_objs,
							const t_light *light, const t_object *filter)
{
	double	tmp;
	t_ray	tmp_ray;

	if (!light->is_in_light((t_light*)light, light_ray) ||
		(!light_ray->equ.vd.x && !light_ray->equ.vd.y && !light_ray->equ.vd.z))
	{
		light_ray->shad_opacity = 1;
		return (1);
	}
	tmp_ray = *light_ray;
	tmp_ray.shad_opacity = 0;
	tmp = check_intersect(&tmp_ray, l_objs, 0, filter);
	light_ray->shad_opacity = tmp_ray.shad_opacity;
	if (gt(tmp, 0) && lt(tmp, 1))
		return (1);
	return (0);
}

SDL_Color	color_mod(SDL_Color src1, SDL_Color src2)
{
	return ((SDL_Color){src1.r * src2.r / 255,
						src1.g * src2.g / 255,
						src1.b * src2.b / 255, 255});
}
