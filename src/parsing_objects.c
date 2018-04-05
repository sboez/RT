/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 15:25:52 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/18 20:05:32 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_box			*parsing_box(char *object)
{
	t_dot		size;
	char		*data[4];
	t_objs_comp	args;

	if (!(data[0] = get_interval(object, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(object, "<material>", "</material>"))
		|| !(data[3] = get_interval(object, "<size>", "</size>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_material(data[1], &args.material) == -1)
		|| (parsing_dot(data[3], &size) == -1))
		return (NULL);
	data[2] = get_interval(object, "<physic>", "</physic>");
	parsing_physic(data[2], &args);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	return (new_box(args, size));
}

t_hyperboloid	*parsing_hyperboloid(char *object)
{
	char		*data[7];
	t_objs_comp	args;
	double		d[4];

	if (!(data[0] = get_interval(object, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(object, "<material>", "</material>"))
		|| !(data[3] = get_interval(object, "<a>", "</a>"))
		|| !(data[4] = get_interval(object, "<b>", "</b>"))
		|| !(data[5] = get_interval(object, "<c>", "</c>"))
		|| !(data[6] = get_interval(object, "<d>", "</d>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_material(data[1], &args.material) == -1))
		return (NULL);
	data[2] = get_interval(object, "<physic>", "</physic>");
	parsing_physic(data[2], &args);
	d[0] = atod(data[3]);
	d[1] = atod(data[4]);
	d[2] = atod(data[5]);
	d[3] = atod(data[6]);
	free_tab(data, 7);
	return (new_hyperboloid(args,
			(t_hyperboloid_args){d[0], d[1], d[2], d[3]}));
}

t_triangle		*parsing_triangle(char *object)
{
	char		*data[5];
	t_objs_comp	args;
	t_dot		d[3];

	if (!(data[0] = get_interval(object, "<material>", "</material>"))
		|| !(data[1] = get_interval(object, "<dot_a>", "</dot_a>"))
		|| !(data[3] = get_interval(object, "<dot_b>", "</dot_b>"))
		|| !(data[4] = get_interval(object, "<dot_c>", "</dot_c>"))
		|| (parsing_material(data[0], &args.material) == -1)
		|| (parsing_dot(data[1], &d[_A]) == -1)
		|| (parsing_dot(data[3], &d[_B]) == -1)
		|| (parsing_dot(data[4], &d[_B]) == -1))
		return (NULL);
	data[2] = get_interval(object, "<physic>", "</physic>");
	parsing_physic(data[2], &args);
	args.orig = (t_dot){(d[_A].x + d[_B].x + d[_C].x) / 3,
						(d[_A].y + d[_B].y + d[_C].y) / 3,
						(d[_A].z + d[_B].z + d[_C].z) / 3};
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	free(data[4]);
	return (new_triangle(args, d[_A], d[_B], d[_C]));
}

t_object		*parsing_object2(char *object, int obj_light)
{
	t_object	*obj;
	char		*data;

	obj = NULL;
	if (!(data = get_interval(object, "<type>", "</type>")))
		return (NULL);
	if (!(ft_strcmp(data, "sphere")))
		obj = (t_object *)parsing_sphere(object);
	else if (!(ft_strcmp(data, "plane")))
		obj = (t_object *)parsing_plane(object);
	else if (!(ft_strcmp(data, "cylinder")))
		obj = (t_object *)parsing_cylinder(object);
	else if (!(ft_strcmp(data, "cone")))
		obj = (t_object *)parsing_cone(object);
	else if (!(ft_strcmp(data, "box")))
		obj = (t_object *)parsing_box(object);
	else if (!(ft_strcmp(data, "hyperboloid")) && obj_light == 0)
		obj = (t_object *)parsing_hyperboloid(object);
	else if (!(ft_strcmp(data, "triangle")) && obj_light == 0)
		obj = (t_object *)parsing_triangle(object);
	free(data);
	return (obj);
}

t_list_objs		*parsing_object(char *scene, t_list_objs *l)
{
	char		*data[4];
	t_object	*obj;

	while ((data[0] = get_interval(scene, "<object>", "</object>")))
	{
		data[1] = get_interval(data[0], "<negative_obj>", "</negative_obj>");
		data[2] = get_interval(data[0], "<limit>", "</limit>");
		data[3] = get_interval(data[0], "<transformations>",
										"</transformations>");
		if ((obj = parsing_object2(data[0], 0)))
		{
			parsing_transformations(obj, data[3]);
			parsing_limit(obj, data[2]);
			parsing_negative_obj(obj, data[1]);
			free(data[0]);
			free(data[1]);
			free(data[2]);
			free(data[3]);
			if (obj->obj_type == BOX)
				box_dependency_lists((t_box*)obj);
			new_cell_obj(&l, obj);
		}
	}
	return (l);
}
