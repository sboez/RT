/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 03:59:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/17 16:15:32 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	is_in_negative_obj(const double *t, const t_ray *ray,
							t_object *father, t_object *except)
{
	t_list_objs	*l;

	l = father->negative_obj;
	while (l)
	{
		if (ray->obj != l->obj && (!except || l->obj != except) &&
			is_in_limited_obj(t, ray, l->obj))
			return (1);
		l = l->next;
	}
	return (0);
}

static void	list_is_not_in_negative_obj(t_list_ray **l_ray, t_couple_ray *neg,
										t_object *neg_obj)
{
	t_list_ray	*l;

	l = *l_ray;
	while (l)
	{
		if (l->r.nb_intersect > 0 && lt(neg->ta, l->t) && lt(l->t, neg->tb) &&
			is_in_limit(&l->r, neg_obj))
			l->r.nb_intersect = 0;
		l = l->next;
	}
}

static void	valid_negative_points(t_list_ray **l_ray, t_couple_ray *neg,
								t_object *father, t_object *except)
{
	if (is_in_limited_obj(&neg->ta, &neg->a, father) &&
		!is_in_negative_obj(&neg->ta, &neg->a, father, except))
		add_cell_ray(l_ray, &neg->a, &neg->ta, 1);
	if (is_in_limited_obj(&neg->tb, &neg->b, father) &&
		!is_in_negative_obj(&neg->tb, &neg->b, father, except))
		add_cell_ray(l_ray, &neg->b, &neg->tb, 2);
}

void		negative_obj(t_list_ray **l_ray, t_couple_ray *basic,
						t_object *father, const t_ray *ray)
{
	t_couple_ray	neg;
	t_list_objs		*l;

	l = &(t_list_objs){NULL, father->negative_obj};
	if (is_in_negative_obj(&basic->ta, &basic->a, father, NULL))
		basic->a.nb_intersect = 0;
	if (is_in_negative_obj(&basic->tb, &basic->b, father, NULL))
		basic->b.nb_intersect = 0;
	while ((l = l->next))
	{
		neg.a = first_intersect(ray, l->obj, &neg.ta);
		neg.b = second_intersect(ray, l->obj, &neg.tb);
		if (neg.a.nb_intersect > 0 && neg.b.nb_intersect > 0)
		{
			transform_inter(&neg.a, l->obj);
			transform_inter(&neg.b, l->obj);
			if (l->obj->limit)
				limit(&neg, l->obj, ray);
			if (neg.a.nb_intersect > 0 && neg.b.nb_intersect > 0)
			{
				list_is_not_in_negative_obj(l_ray, &neg, l->obj);
				valid_negative_points(l_ray, &neg, father, l->obj);
			}
		}
	}
}
