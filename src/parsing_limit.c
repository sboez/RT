/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_limit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 01:57:03 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/20 13:35:57 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "texture_mapping.h"

void	parsing_global_limit(t_object *o, t_dot origin, t_vector normal,
							int status)
{
	t_plane	*p;

	p = new_plane((t_objs_comp){origin, o->material,
								o->obj_light.reflection_amount,
								o->obj_light.refraction_amount,
								o->obj_light.refractive_index,
								o->obj_light.shininess}, normal, 0);
	p->status = status;
	new_cell_obj(&o->limit, (t_object *)p);
}

void	parsing_local_limit(t_object *o, t_dot origin, t_vector normal,
							int status)
{
	t_plane	*p;

	mult_vect((t_vector*)&origin, o->trans_const, (t_vector*)&origin);
	mult_vect(&normal, o->trans_norm, &normal);
	origin.x += o->origin.x;
	origin.y += o->origin.y;
	origin.z += o->origin.z;
	p = new_plane((t_objs_comp){origin, o->material,
								o->obj_light.reflection_amount,
								o->obj_light.refraction_amount,
								o->obj_light.refractive_index,
								o->obj_light.shininess}, normal, 0);
	p->status = status;
	new_cell_obj(&o->limit, (t_object *)p);
}

void	global_loop(t_object *obj, char *limit)
{
	char		*data[4];
	t_dot		origin;
	t_vector	normal;
	int			status;

	init_tab(data, 4);
	status = EMPTY;
	while ((data[0] = get_interval(limit, "<global>", "</global>")))
	{
		if (!(data[1] = get_interval(data[0], "<origin>", "</origin>"))
			|| !(data[2] = get_interval(data[0], "<normal>", "</normal>"))
			|| !(data[3] = get_interval(data[0], "<status>", "</status>"))
			|| (parsing_dot(data[1], &origin) == -1)
			|| (parsing_vector(data[2], &normal) == -1)
			|| ((status = get_status(data[3])) == -1))
			exit_custom_error("rt", ":global_loop failed");
		parsing_global_limit(obj, origin, normal, status);
		free(data[0]);
		free(data[1]);
		free(data[2]);
		free(data[3]);
	}
}

void	local_loop(t_object *obj, char *limit)
{
	char		*data[4];
	t_dot		origin;
	t_vector	normal;
	int			status;

	init_tab(data, 4);
	status = EMPTY;
	while ((data[0] = get_interval(limit, "<local>", "</local>")))
	{
		if (!(data[1] = get_interval(data[0], "<origin>", "</origin>"))
			|| !(data[2] = get_interval(data[0], "<normal>", "</normal>"))
			|| !(data[3] = get_interval(data[0], "<status>", "</status>"))
			|| (parsing_dot(data[1], &origin) == -1)
			|| (parsing_vector(data[2], &normal) == -1)
			|| ((status = get_status(data[3])) == -1))
			exit_custom_error("rt", ":local_loop failed");
		parsing_local_limit(obj, origin, normal, status);
		free(data[0]);
		free(data[1]);
		free(data[2]);
		free(data[3]);
	}
}

void	parsing_limit(t_object *obj, char *limit)
{
	if (limit)
	{
		local_loop(obj, limit);
		global_loop(obj, limit);
	}
}
