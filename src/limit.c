/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 10:27:56 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/18 19:16:06 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			is_in_right_side_of_limit(const t_dot *i, const t_plane *p)
{
	double	distance_1;
	double	distance_2;

	distance_1 = get_dot_dist(i, &(t_dot){(p->origin.x + p->normal.x),
										(p->origin.y + p->normal.y),
										(p->origin.z + p->normal.z)});
	distance_2 = get_dot_dist(i, &(t_dot){(p->origin.x - p->normal.x),
										(p->origin.y - p->normal.y),
										(p->origin.z - p->normal.z)});
	return (ge(distance_1, distance_2));
}

int			is_in_limit(const t_ray *ray, t_object *father)
{
	t_list_objs	*l;

	l = father->limit;
	while (l)
	{
		if (ray->obj != l->obj &&
			!is_in_right_side_of_limit(&ray->inter, (t_plane*)l->obj))
			return (0);
		l = l->next;
	}
	return (1);
}

static void	init_limit_norme(t_couple_ray *basic, t_object *father,
							t_couple_ray *limited)
{
	if (is_in_limit(&basic->a, father))
		limit2(limited, &basic->a, &basic->ta);
	else
		basic->a.nb_intersect = 0;
	if (is_in_limit(&basic->b, father))
		limit2(limited, &basic->b, &basic->tb);
	else
		basic->b.nb_intersect = 0;
}

void		limit(t_couple_ray *basic, t_object *father, const t_ray *ray)
{
	t_couple_ray	limited;
	t_list_objs		*l;
	t_ray			tmp;
	double			t_tmp;

	l = father->limit;
	limited.a.nb_intersect = 0;
	limited.b.nb_intersect = 0;
	init_limit_norme(basic, father, &limited);
	while (l)
	{
		tmp = first_intersect(ray, l->obj, &t_tmp);
		if (tmp.nb_intersect > 0)
		{
			transform_inter(&tmp, l->obj);
			if (is_in_limit(&tmp, father) &&
				is_in_obj(t_tmp, tmp.inter, father))
				limit2(&limited, &tmp, &t_tmp);
		}
		l = l->next;
	}
	if (limited.a.nb_intersect > 0 && limited.b.nb_intersect > 0)
		*basic = limited;
}
