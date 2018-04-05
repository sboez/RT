/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:56:42 by shiro             #+#    #+#             */
/*   Updated: 2018/02/19 12:24:18 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "texture_mapping.h"

void	box_dependency_lists(t_box *box)
{
	if (box->limit)
	{
		box->front->limit = box->limit;
		box->back->limit = box->limit;
		box->bottom->limit = box->limit;
		box->top->limit = box->limit;
		box->left->limit = box->limit;
		box->right->limit = box->limit;
	}
	if (box->negative_obj)
	{
		box->front->negative_obj = box->negative_obj;
		box->back->negative_obj = box->negative_obj;
		box->bottom->negative_obj = box->negative_obj;
		box->top->negative_obj = box->negative_obj;
		box->left->negative_obj = box->negative_obj;
		box->right->negative_obj = box->negative_obj;
	}
}

void	box_transform_planes(t_box *box, t_trans_data trs)
{
	t_dot	t;

	t = trs.trans;
	trs.trans = (t_dot){t.x - (box->size.x / 2), t.y, t.z};
	set_all_matrix((t_object *)box->front, trs);
	trs.trans = (t_dot){t.x, t.y - (box->size.y / 2), t.z};
	set_all_matrix((t_object *)box->bottom, trs);
	trs.trans = (t_dot){t.x, t.y, t.z - (box->size.z / 2)};
	set_all_matrix((t_object *)box->left, trs);
	trs.trans = (t_dot){t.x + (box->size.x / 2), t.y, t.z};
	set_all_matrix((t_object *)box->back, trs);
	trs.trans = (t_dot){t.x, t.y + (box->size.y / 2), t.z};
	set_all_matrix((t_object *)box->top, trs);
	trs.trans = (t_dot){t.x, t.y, t.z + (box->size.z / 2)};
	set_all_matrix((t_object *)box->right, trs);
	if ((box->material.texture || box->material.chess) &&
		box->material.texture_mapping == planar_mapping)
	{
		box->front->material.texture_mapping = planar_mapping_x;
		box->bottom->material.texture_mapping = planar_mapping_y;
		box->left->material.texture_mapping = planar_mapping_z;
		box->back->material.texture_mapping = planar_mapping_x;
		box->top->material.texture_mapping = planar_mapping_y;
		box->right->material.texture_mapping = planar_mapping_z;
	}
}

int		is_in_box_boundaries(const t_plane *p, t_box *b, t_dot *d)
{
	if (p == b->front || p == b->back)
		return (le(d->z, b->btr_corner.z) && gt(d->z, b->fbl_corner.z) &&
				le(d->y, b->btr_corner.y) && gt(d->y, b->fbl_corner.y));
	else if (p == b->top || p == b->bottom)
		return (le(d->x, b->btr_corner.x) && gt(d->x, b->fbl_corner.x) &&
				le(d->z, b->btr_corner.z) && gt(d->z, b->fbl_corner.z));
	else if (p == b->left || p == b->right)
		return (le(d->y, b->btr_corner.y) && gt(d->y, b->fbl_corner.y) &&
				le(d->x, b->btr_corner.x) && gt(d->x, b->fbl_corner.x));
	else
		return (0);
}

void	delete_box(t_box *box)
{
	delete_plane(box->back);
	delete_plane(box->front);
	delete_plane(box->bottom);
	delete_plane(box->top);
	delete_plane(box->left);
	delete_plane(box->right);
	delete_object((t_object*)box);
}
