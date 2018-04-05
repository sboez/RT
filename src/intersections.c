/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/20 13:42:45 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		choice_intersect(t_list_ray *l, t_ray *ray, double *dist)
{
	while (l)
	{
		if (l->r.nb_intersect > 0 &&
			(!l->r.obj->material.transparency ||
				!coloreq(l->r.color, l->r.obj->material.transparent_color)))
		{
			if (eq(*dist, 0) || (gt(*dist, 0) && lt(l->t, *dist)))
			{
				if (l->r.obj->status != EMPTY)
				{
					*dist = l->t;
					*ray = l->r;
					ray->i_intersect = l->i;
				}
			}
		}
		delete_cell_ray(&l);
	}
}

static void	check_intersect2(t_ray *ray, const t_list_objs *l, double *dist)
{
	t_couple_ray	basic;
	t_list_ray		*l_ray;

	basic.a = first_intersect(ray, l->obj, &basic.ta);
	basic.b = second_intersect(ray, l->obj, &basic.tb);
	if (basic.a.nb_intersect > 0 && basic.b.nb_intersect > 0)
	{
		l_ray = NULL;
		transform_inter(&basic.a, l->obj);
		transform_inter(&basic.b, l->obj);
		if (l->obj->limit)
			limit(&basic, l->obj, ray);
		if (l->obj->negative_obj)
			negative_obj(&l_ray, &basic, l->obj, ray);
		add_cell_ray(&l_ray, &basic.a, &basic.ta, 1);
		add_cell_ray(&l_ray, &basic.b, &basic.tb, 2);
		choice_intersect(l_ray, ray, dist);
	}
}

double		check_intersect(t_ray *ray, const t_list_objs *l, int check_lights,
							const t_object *filter)
{
	double	dist;

	dist = 0;
	ray->obj = NULL;
	while (l)
	{
		if ((!l->obj->is_light || check_lights) &&
			(!filter || l->obj != filter))
			check_intersect2(ray, l, &dist);
		l = l->next;
	}
	if (ray->obj && !ray->obj->material.normal_map)
		correct_normal((t_dot){ray->equ.vc.x, ray->equ.vc.y, ray->equ.vc.z},
						ray->inter, &ray->normal);
	return (dist);
}

t_ray		first_intersect(const t_ray *ray, t_object *obj, double *tmp)
{
	t_ray			tmp_ray;
	t_parequation	e;

	tmp_ray = *ray;
	tmp_ray.obj = obj;
	e = transform_equ(&tmp_ray, obj);
	*tmp = obj->intersect(&tmp_ray, e, obj, 1);
	if (obj->material.texture || obj->material.chess)
		tmp_ray.color = get_text_color(tmp_ray.inter, tmp_ray.obj);
	else
		tmp_ray.color = obj->material.color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.normal = tmp_ray.obj->get_normal(&tmp_ray.inter, tmp_ray.obj);
	if (gt(*tmp, 0))
		tmp_ray.shad_opacity += (1 - tmp_ray.obj->obj_light.refraction_amount);
	return (tmp_ray);
}

t_ray		second_intersect(const t_ray *ray, t_object *obj, double *tmp)
{
	t_ray			tmp_ray;
	t_parequation	e;

	tmp_ray = *ray;
	tmp_ray.obj = obj;
	e = transform_equ(&tmp_ray, obj);
	*tmp = obj->intersect(&tmp_ray, e, obj, 2);
	if (obj->material.texture || obj->material.chess)
		tmp_ray.color = get_text_color(tmp_ray.inter, tmp_ray.obj);
	else
		tmp_ray.color = obj->material.color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.normal = tmp_ray.obj->get_normal(&tmp_ray.inter, tmp_ray.obj);
	if (gt(*tmp, 0))
		tmp_ray.shad_opacity += (1 - tmp_ray.obj->obj_light.refraction_amount);
	return (tmp_ray);
}
