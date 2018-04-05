/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/18 21:25:11 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_parequation	transform_equ(t_ray *ray, t_object *obj)
{
	t_parequation	trs;

	trs.vc = (t_vector){ray->equ.vc.x - obj->origin.x,
						ray->equ.vc.y - obj->origin.y,
						ray->equ.vc.z - obj->origin.z};
	mult_vect(&trs.vc, obj->trans_iconst, &trs.vc);
	mult_vect(&trs.vd, obj->trans_idir, &ray->equ.vd);
	return (trs);
}

void			transform_inter(t_ray *ray, t_object *obj)
{
	mult_vect(&ray->normal, ray->obj->trans_norm, &ray->normal);
	mult_vect((t_vector*)&ray->inter, ray->obj->trans_const,
			(t_vector*)&ray->inter);
	ray->inter = (t_dot){ray->inter.x + ray->obj->origin.x,
						ray->inter.y + ray->obj->origin.y,
						ray->inter.z + ray->obj->origin.z};
	ray->obj = obj;
}

void			correct_normal(t_dot dot, t_dot inter, t_vector *normal)
{
	double	d1;
	double	d2;

	d1 = get_dot_dist(&dot, &(t_dot){inter.x + normal->x,
									inter.y + normal->y,
									inter.z + normal->z});
	d2 = get_dot_dist(&dot, &(t_dot){inter.x - normal->x,
									inter.y - normal->y,
									inter.z - normal->z});
	if (!lt(d1, d2))
		*normal = (t_vector){-normal->x, -normal->y, -normal->z};
}

void			valid_ray(t_ray *r1, double *t_r1, t_ray *r2, double *t_r2)
{
	*r1 = *r2;
	*t_r1 = *t_r2;
}

SDL_Color		effects(t_ray *ray, t_scene *scn)
{
	SDL_Color	reflect_ray;
	SDL_Color	refract_ray;

	if (check_intersect(ray, scn->objects, 1, NULL) > 0)
	{
		if (ray->obj->is_light)
			return (ray->color);
		ray->color = shadows(ray, scn);
		reflect_ray = reflect(ray, scn);
		refract_ray = refract(ray, scn);
		get_reflected_col(ray, ray->obj, reflect_ray);
		get_refracted_col(ray, ray->obj, refract_ray);
		return (ray->color);
	}
	return (ray->color = (SDL_Color){0, 0, 0, 0});
}
