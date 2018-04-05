/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shading.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 13:54:41 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/19 16:04:05 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_SHADING_H
# define LIGHT_SHADING_H
# include "structures.h"

/*
**light_shading.c
*/
SDL_Color	get_shade_col(const t_ray *light_ray, double opacity, double *coef);
SDL_Color	get_specular_col(const t_ray *ray, const t_ray *light_ray,
							double opacity, int shade);

/*
**shadows.c
*/
int			check_objs_on_ray(t_ray *light_ray, const t_list_objs *l_objs,
							const t_light *light, const t_object *filter);
SDL_Color	shadows(t_ray *ray, t_scene *scn);
SDL_Color	color_mod(SDL_Color src1, SDL_Color src2);

#endif
