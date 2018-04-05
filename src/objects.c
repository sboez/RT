/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:32:56 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/23 14:07:51 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static size_t	get_type_size(t_type type)
{
	return ((size_t[7]){sizeof(t_box), sizeof(t_cone), sizeof(t_cylinder),
						sizeof(t_hyperboloid), sizeof(t_plane),
						sizeof(t_sphere), sizeof(t_triangle)}[type]);
}

t_object		*new_object(t_type type, t_objs_comp args)
{
	t_object	*obj;

	if (!(obj = malloc(get_type_size(type))))
		exit_error("rt", "malloc");
	*(t_type*)&obj->obj_type = type;
	obj->origin = args.orig;
	obj->material = args.material;
	obj->obj_light = (t_obj_phys){args.reflection_amount,
								args.refraction_amount, args.refractive_index,
								args.shininess};
	obj->get_normal = NULL;
	obj->intersect = NULL;
	obj->is_in_obj = NULL;
	obj->limit = NULL;
	obj->negative_obj = NULL;
	obj->status = FULL;
	obj->trans_const = create_identity(4);
	obj->trans_iconst = create_identity(4);
	obj->trans_idir = create_identity(4);
	obj->trans_norm = create_identity(4);
	obj->is_light = 0;
	return (obj);
}

void			set_all_matrix(t_object *object, t_trans_data data)
{
	scale(&object->trans_const, data.scale.x, data.scale.y, data.scale.z);
	x_rotation(&object->trans_const, data.rot.x);
	y_rotation(&object->trans_const, data.rot.y);
	z_rotation(&object->trans_const, data.rot.z);
	translation(&object->trans_const, data.trans.x, data.trans.y, data.trans.z);
	get_inv_4x4mat(object->trans_iconst, object->trans_const);
	scale(&object->trans_idir, data.scale.x, data.scale.y, data.scale.z);
	x_rotation(&object->trans_idir, data.rot.x);
	y_rotation(&object->trans_idir, data.rot.y);
	z_rotation(&object->trans_idir, data.rot.z);
	get_inv_4x4mat(object->trans_idir, object->trans_idir);
	scale(&object->trans_norm, data.scale.x, data.scale.y, data.scale.z);
	get_inv_4x4mat(object->trans_norm, object->trans_norm);
	x_rotation(&object->trans_norm, data.rot.x);
	y_rotation(&object->trans_norm, data.rot.y);
	z_rotation(&object->trans_norm, data.rot.z);
}

void			delete_object(t_object *obj)
{
	if (obj)
	{
		if (obj->material.texture)
			SDL_FreeSurface(obj->material.texture);
		if (obj->material.normal_map)
			SDL_FreeSurface(obj->material.normal_map);
		delete_matrix(obj->trans_const);
		delete_matrix(obj->trans_iconst);
		delete_matrix(obj->trans_idir);
		delete_matrix(obj->trans_norm);
		while (obj->limit)
		{
			obj->limit->obj->material.normal_map = NULL;
			obj->limit->obj->material.texture = NULL;
			delete_cell_obj(&obj->limit);
		}
		while (obj->negative_obj)
			delete_cell_obj(&obj->negative_obj);
		free(obj);
	}
}
