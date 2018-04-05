/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 12:33:37 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/18 20:03:29 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "texture_mapping.h"
#include <math.h>

static double	sphere_intersect(t_ray *ray, t_parequation e, t_object *obj,
								int i)
{
	t_sphere	*s;
	double		t;
	double		fac[3];

	s = (t_sphere*)obj;
	t = -1;
	fac[_A] = e.vd.x * e.vd.x + e.vd.y * e.vd.y + e.vd.z * e.vd.z;
	fac[_B] = 2 * (e.vd.x * e.vc.x + e.vd.y * e.vc.y + e.vd.z * e.vc.z);
	fac[_C] = e.vc.x * e.vc.x + e.vc.y * e.vc.y + e.vc.z * e.vc.z - s->r2;
	if ((ray->nb_intersect = get_quad_equation_sol(&t, fac, i)))
	{
		ray->inter = equation_get_dot(&e, t);
		ray->obj = obj;
	}
	return (t);
}

static t_vector	get_sphere_normal(t_dot *inter, t_object *obj)
{
	t_vector	tmp;

	if (obj->material.normal_map)
	{
		tmp = get_map_vector(*inter, obj);
		tmp.x *= 2 * inter->x;
		tmp.y *= 2 * inter->y;
		tmp.z *= 2 * inter->z;
		return (tmp);
	}
	return ((t_vector){2 * inter->x, 2 * inter->y, 2 * inter->z});
}

static int		is_in_sphere(t_dot *i, t_object *obj)
{
	t_sphere	*s;

	s = (t_sphere*)obj;
	return ((pow(i->x, 2) + pow(i->y, 2) + pow(i->z, 2) <= s->r2));
}

t_sphere		*new_sphere(t_objs_comp args, double radius)
{
	t_sphere	*sphere;

	sphere = (t_sphere*)new_object(SPHERE, args);
	sphere->radius = radius;
	sphere->get_normal = get_sphere_normal;
	sphere->is_in_obj = is_in_sphere;
	sphere->intersect = sphere_intersect;
	sphere->r2 = pow(radius, 2);
	return (sphere);
}

void			delete_sphere(t_sphere *sphere)
{
	delete_object((t_object*)sphere);
}
