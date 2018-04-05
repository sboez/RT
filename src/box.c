/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 17:09:17 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/18 19:14:06 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		box_plane_intersect(t_ray *ray, const t_plane *p,
										t_parequation e, t_box_intersect *its)
{
	double	t;

	e = transform_equ(ray, (t_object *)p);
	t = p->intersect(ray, e, (t_object*)p, 0);
	if (is_in_box_boundaries(p, its->box, &ray->inter))
	{
		if (its->t == -1)
			ray->nb_intersect = 1;
		else
			ray->nb_intersect = 2;
		if ((its->i == 1 && (lt(t, its->t) || eq(its->t, 0))) ||
			(its->i == 2 && (gt(t, its->t) || eq(its->t, 0))))
		{
			its->p = (t_plane*)p;
			its->inter = ray->inter;
			its->t = t;
		}
	}
}

static double	box_intersect(t_ray *ray, t_parequation e, t_object *obj, int i)
{
	t_box_intersect	its;

	its = (t_box_intersect){(t_box*)obj, (t_dot){0, 0, 0}, i, 0, NULL};
	box_plane_intersect(ray, its.box->back, e, &its);
	box_plane_intersect(ray, its.box->front, e, &its);
	box_plane_intersect(ray, its.box->bottom, e, &its);
	box_plane_intersect(ray, its.box->top, e, &its);
	box_plane_intersect(ray, its.box->left, e, &its);
	box_plane_intersect(ray, its.box->right, e, &its);
	ray->inter = its.inter;
	if (its.p)
		ray->obj = (t_object *)its.p;
	return (its.t);
}

static t_vector	get_box_normal(t_dot *inter, t_object *obj)
{
	t_box	*b;

	b = (t_box*)obj;
	if (b->front->is_in_obj(inter, (t_object*)b->front))
		return (b->front->get_normal(inter, (t_object*)b->front));
	else if (b->back->is_in_obj(inter, (t_object*)b->back))
		return (b->back->get_normal(inter, (t_object*)b->back));
	else if (b->bottom->is_in_obj(inter, (t_object*)b->bottom))
		return (b->bottom->get_normal(inter, (t_object*)b->bottom));
	else if (b->top->is_in_obj(inter, (t_object*)b->top))
		return (b->top->get_normal(inter, (t_object*)b->top));
	else if (b->left->is_in_obj(inter, (t_object*)b->left))
		return (b->left->get_normal(inter, (t_object*)b->left));
	else
		return (b->right->get_normal(inter, (t_object*)b->right));
}

static int		is_in_box(t_dot *i, t_object *obj)
{
	t_box	*b;

	b = (t_box*)obj;
	if (b->front->is_in_obj(i, (t_object*)b->front))
		return (is_in_box_boundaries(b->front, b, i));
	else if (b->back->is_in_obj(i, (t_object*)b->back))
		return (is_in_box_boundaries(b->back, b, i));
	else if (b->bottom->is_in_obj(i, (t_object*)b->bottom))
		return (is_in_box_boundaries(b->bottom, b, i));
	else if (b->top->is_in_obj(i, (t_object*)b->top))
		return (is_in_box_boundaries(b->top, b, i));
	else if (b->left->is_in_obj(i, (t_object*)b->left))
		return (is_in_box_boundaries(b->left, b, i));
	else if (b->right->is_in_obj(i, (t_object*)b->right))
		return (is_in_box_boundaries(b->right, b, i));
	return (0);
}

t_box			*new_box(t_objs_comp args, t_dot size)
{
	t_box	*box;

	box = (t_box*)new_object(BOX, args);
	box->size = size;
	box->fbl_corner = (t_dot){-(size.x / 2), -(size.y / 2), -(size.z / 2)};
	box->btr_corner = (t_dot){(size.x / 2), (size.y / 2), (size.z / 2)};
	box->front = new_plane(args, (t_vector){-1, 0, 0}, 0);
	box->bottom = new_plane(args, (t_vector){0, -1, 0}, 0);
	box->left = new_plane(args, (t_vector){0, 0, -1}, 0);
	box->back = new_plane(args, (t_vector){1, 0, 0}, 0);
	box->top = new_plane(args, (t_vector){0, 1, 0}, 0);
	box->right = new_plane(args, (t_vector){0, 0, 1}, 0);
	box->intersect = &box_intersect;
	box->is_in_obj = &is_in_box;
	box->get_normal = &get_box_normal;
	return (box);
}
