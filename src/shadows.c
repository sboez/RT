/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 11:22:51 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/20 13:48:07 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static SDL_Color	add_colors(SDL_Color dst, SDL_Color src)
{
	SDL_Color	res;

	res.r = (dst.r + src.r) < 255 ? dst.r + src.r : 255;
	res.g = (dst.g + src.g) < 255 ? dst.g + src.g : 255;
	res.b = (dst.b + src.b) < 255 ? dst.b + src.b : 255;
	return (res);
}

static SDL_Color	div_colors(SDL_Color src, t_scene *scn)
{
	SDL_Color	dst;

	dst.r = src.r * scn->brightness;
	dst.g = src.g * scn->brightness;
	dst.b = src.b * scn->brightness;
	return (dst);
}

static void			opacify_color(t_ray *light_ray, double *opacity)
{
	*opacity = 1 - ft_dmin(light_ray->shad_opacity, 1);
	light_ray->color.r *= (*opacity);
	light_ray->color.g *= (*opacity);
	light_ray->color.b *= (*opacity);
}

static void			set_multi_light_norme(const t_ray *light_ray,
										const t_ray *ray,
										SDL_Color *multi_lights,
										t_saloperie_de_norme_de_merde *so)
{
	*multi_lights = add_colors(
						color_mod(*multi_lights, light_ray->light->color),
						add_colors(get_specular_col(ray, light_ray, so->opacity,
													so->shade),
									get_shade_col(light_ray, so->opacity,
													&so->shade)));
}

SDL_Color			shadows(t_ray *ray, t_scene *scn)
{
	t_list_lights					*tmp;
	t_ray							light_ray;
	SDL_Color						multi_lights;
	t_saloperie_de_norme_de_merde	so;

	multi_lights = div_colors(ray->color, scn);
	tmp = scn->lights;
	while (tmp != NULL)
	{
		light_ray.equ.vd = tmp->light->get_ray_vect(ray->inter, tmp->light);
		light_ray.equ.vc = (t_vector){ray->inter.x, ray->inter.y, ray->inter.z};
		light_ray.color = ray->color;
		so.opacity = 1;
		if (check_objs_on_ray(&light_ray, scn->objects, tmp->light,
							ray->i_intersect == 1 ? ray->obj : NULL))
			opacify_color(&light_ray, &so.opacity);
		light_ray.normal = ray->normal;
		light_ray.light = tmp->light;
		set_multi_light_norme(&light_ray, ray, &multi_lights, &so);
		tmp = tmp->next;
	}
	multi_lights.a = 255;
	return (multi_lights);
}
