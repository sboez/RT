/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 15:30:32 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/17 16:36:03 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cone_obj_light(double power, t_cone *obj, t_list_lights **l)
{
	t_cone	*c;

	c = new_cone((t_objs_comp){obj->origin, obj->material,
							obj->obj_light.reflection_amount,
							obj->obj_light.refraction_amount,
							obj->obj_light.refractive_index,
							obj->obj_light.shininess}, obj->angle);
	c->upper = 1;
	obj->upper = 0;
	new_cell_light(l, (t_light*)new_obj_light(power, (t_object*)c));
}

t_obj_light		*parsing_obj_light(char *light, t_list_lights **l)
{
	t_object	*obj;
	double		power;
	char		*data[5];

	if (!(data[0] = get_interval(light, "<shape>", "</shape>")) ||
		!(data[4] = get_interval(light, "<power>", "</power>")))
		return (NULL);
	data[1] = get_interval(data[0], "<negative_obj>", "</negative_obj>");
	data[2] = get_interval(data[0], "<limit>", "</limit>");
	data[3] = get_interval(data[0], "<transformations>", "</transformations>");
	if (!(obj = parsing_object2(data[0], 1)))
		return (NULL);
	parsing_transformations(obj, data[3]);
	parsing_limit(obj, data[2]);
	parsing_negative_obj(obj, data[1]);
	power = atod(data[4]);
	if (obj->obj_type == BOX)
		box_dependency_lists((t_box*)obj);
	if (obj->obj_type == CONE)
		cone_obj_light(power, (t_cone*)obj, l);
	free_tab(data, 5);
	return (new_obj_light(power, obj));
}

t_light			*parsing_light2(char *light, char *light_type,
								t_list_lights **l)
{
	t_light	*lux;

	lux = NULL;
	if (!(ft_strcmp(light_type, "orb")))
		lux = (t_light *)parsing_orb_light(light);
	else if (!(ft_strcmp(light_type, "parallel")))
		lux = (t_light *)parsing_parallel_light(light);
	else if (!(ft_strcmp(light_type, "spot")))
		lux = (t_light *)parsing_spotlight(light);
	else if (!(ft_strcmp(light_type, "object")))
		lux = (t_light *)parsing_obj_light(light, l);
	return (lux);
}

t_list_lights	*parsing_light(char *scene, t_list_objs **l_objs)
{
	char			*data[2];
	t_light			*lux;
	t_list_lights	*l;

	l = NULL;
	while ((data[0] = get_interval(scene, "<light>", "</light>")))
	{
		if (!(data[1] = get_interval(data[0], "<type>", "</type>")))
			return (NULL);
		if (!(lux = parsing_light2(data[0], data[1], &l)))
			return (NULL);
		free(data[1]);
		free(data[0]);
		new_cell_light(&l, lux);
		if (lux->type == OBJECT)
			new_cell_obj(l_objs, ((t_obj_light*)lux)->shape);
	}
	return (l);
}
