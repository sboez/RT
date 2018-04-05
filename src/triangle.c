/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:16:14 by shiro             #+#    #+#             */
/*   Updated: 2018/02/18 21:46:42 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	triangle_intersect(t_ray *ray, t_parequation e, t_object *obj,
								int i)
{
	double		t;
	t_triangle	*tgl;
	t_dot		itmp;

	tgl = (t_triangle*)obj;
	if (gt(t = plane_intersect(ray, e, obj, i), 0))
	{
		itmp = (t_dot){ray->inter.x + tgl->origin.x,
						ray->inter.y + tgl->origin.y,
						ray->inter.z + tgl->origin.z};
		if (gt(angle_between_vectors(tgl->v_ab, dots_to_vect(tgl->d_a, itmp)),
				tgl->a_a) ||
			gt(angle_between_vectors(tgl->v_ba, dots_to_vect(tgl->d_b, itmp)),
				tgl->a_b) ||
			gt(angle_between_vectors(tgl->v_bc, dots_to_vect(tgl->d_b, itmp)),
				tgl->a_b))
			t = -1;
	}
	return (t);
}

static int		is_in_triangle(t_dot *i, t_object *obj)
{
	double		res;
	t_triangle	*tgl;

	tgl = (t_triangle*)obj;
	res = tgl->a * i->x + tgl->b * i->y + tgl->c * i->z + tgl->d;
	if (!(gt(res, 0) || lt(res, 0)))
	{
		if (gt(angle_between_vectors(tgl->v_ab, dots_to_vect(tgl->d_b, *i)),
				tgl->a_a) ||
			gt(angle_between_vectors(tgl->v_ba, dots_to_vect(tgl->d_b, *i)),
				tgl->a_b) ||
			gt(angle_between_vectors(tgl->v_bc, dots_to_vect(tgl->d_b, *i)),
				tgl->a_b))
			return (0);
		return (1);
	}
	return (0);
}

t_triangle		*new_triangle(t_objs_comp args, t_dot d_a, t_dot d_b, t_dot d_c)
{
	t_triangle	*triangle;

	triangle = (t_triangle*)new_plane(args,
									vect_cross_product(dots_to_vect(d_a, d_b),
													dots_to_vect(d_a, d_c)), 1);
	triangle->v_ab = dots_to_vect(d_a, d_b);
	triangle->v_ba = dots_to_vect(d_b, d_a);
	triangle->v_bc = dots_to_vect(d_b, d_c);
	triangle->a_a = fabs(angle_between_vectors(triangle->v_ab,
											dots_to_vect(d_a, d_c)));
	triangle->a_b = fabs(angle_between_vectors(triangle->v_ba,
											dots_to_vect(d_b, d_c)));
	triangle->d_a = d_a;
	triangle->d_b = d_b;
	triangle->d_c = d_c;
	triangle->intersect = &triangle_intersect;
	triangle->is_in_obj = &is_in_triangle;
	return (triangle);
}

void			delete_triangle(t_triangle *triangle)
{
	delete_plane((t_plane*)triangle);
}
