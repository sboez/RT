/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:53:24 by shiro             #+#    #+#             */
/*   Updated: 2018/02/20 20:05:11 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_dot	get_sphere_ray_vect(t_dot pos, t_obj_light *obl)
{
	t_dot	res;
	double	t;
	double	r;

	res = (t_dot){pos.x - obl->shape->origin.x, pos.y - obl->shape->origin.y,
				pos.z - obl->shape->origin.z};
	mult_vect((t_vector*)&res, obl->shape->trans_iconst, (t_vector*)&res);
	if (eq(res.x, 0) && eq(res.y, 0) && eq(res.z, 0))
		return (pos);
	r = ((t_sphere*)obl->shape)->radius;
	t = -0.5 + sqrt(res.x * res.x + res.y * res.y + res.z * res.z) / (2 * r);
	res = (t_dot){res.x / (1 + 2 * t), res.y / (1 + 2 * t),
				res.z / (1 + 2 * t)};
	if (obl->shape->material.texture && !obl->shape->material.color.a)
		obl->color = get_text_color(res, obl->shape);
	mult_vect((t_vector*)&res, obl->shape->trans_const, (t_vector*)&res);
	return ((t_dot){res.x + obl->shape->origin.x, res.y + obl->shape->origin.y,
					res.z + obl->shape->origin.z});
}

static t_vector	get_obj_ray_vect(t_dot pos, t_light *light)
{
	t_obj_light	*obl;
	t_dot		dot;
	t_ray		tmp;

	obl = (t_obj_light*)light;
	if (obl->shape->obj_type == SPHERE)
		dot = get_sphere_ray_vect(pos, obl);
	else if (obl->shape->obj_type == CONE)
		dot = get_cone_ray_vect(pos, obl);
	else if (obl->shape->obj_type == CYLINDER)
		dot = get_cylinder_ray_vect(pos, obl);
	else if (obl->shape->obj_type == PLANE)
		dot = get_plane_ray_vect(pos, obl);
	else if (obl->shape->obj_type == BOX)
		dot = get_box_ray_vect(pos, obl);
	else
		dot = obl->shape->origin;
	tmp.inter = dot;
	if (!is_in_limit(&tmp, obl->shape))
		return ((t_vector){0, 0, 0});
	return ((t_vector){dot.x - pos.x, dot.y - pos.y, dot.z - pos.z});
}

static int		is_in_obj_light(t_light *light, t_ray *light_ray)
{
	(void)light;
	return (!(eq(light_ray->equ.vd.x, 0) && eq(light_ray->equ.vd.y, 0) &&
			eq(light_ray->equ.vd.z, 0)));
}

t_obj_light		*new_obj_light(double power, t_object *obj)
{
	t_obj_light	*obl;

	obl = (t_obj_light*)new_light(OBJECT, (t_vector){0, 0, 0},
								obj->material.color, power);
	obj->is_light = 1;
	obl->shape = obj;
	obl->is_in_light = is_in_obj_light;
	obl->get_ray_vect = get_obj_ray_vect;
	return (obl);
}

void			delete_obj_light(t_obj_light *obl)
{
	delete_light((t_light*)obl);
}
