/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 12:42:42 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/19 16:04:09 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

SDL_Color	get_shade_col(const t_ray *light_ray, double opacity, double *coef)
{
	SDL_Color	col;
	t_vector	tmp_col;

	col = light_ray->color;
	*coef = (vect_dot_product(light_ray->equ.vd, light_ray->normal) /
			(get_vect_lenght(&light_ray->equ.vd) *
				get_vect_lenght(&light_ray->normal)));
	if (lt(*coef, 0))
		*coef = 0;
	tmp_col.x = col.r * (*coef) * opacity;
	tmp_col.y = col.g * (*coef) * opacity;
	tmp_col.z = col.b * (*coef) * opacity;
	*coef = gt(*coef, 0) ? 1 : 0;
	col = (SDL_Color){tmp_col.x > 255 ? 255 : tmp_col.x,
					tmp_col.y > 255 ? 255 : tmp_col.y,
					tmp_col.z > 255 ? 255 : tmp_col.z, 255};
	return (col);
}

SDL_Color	get_specular_col(const t_ray *ray, const t_ray *light_ray,
							double opacity, int shade)
{
	t_vector	r;
	t_vector	v;
	double		coef;

	if (!shade)
		return ((SDL_Color){0, 0, 0, 255});
	r = get_reflected_vect(&ray->equ.vd, &ray->normal);
	vect_normalize(&r);
	v = light_ray->equ.vd;
	vect_normalize(&v);
	coef = !ray->obj->obj_light.shininess ? 0 :
		(light_ray->light->power *
			pow(vect_dot_product(r, v), ray->obj->obj_light.shininess));
	r.x = light_ray->light->color.r * coef * opacity;
	r.y = light_ray->light->color.g * coef * opacity;
	r.z = light_ray->light->color.b * coef * opacity;
	return ((SDL_Color){r.x > 255 ? 255 : r.x,
						r.y > 255 ? 255 : r.y,
						r.z > 255 ? 255 : r.z, 255});
}
