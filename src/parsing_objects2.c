/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 15:25:52 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/17 16:45:10 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_plane		*parsing_plane(char *object)
{
	char		*data[4];
	t_objs_comp	args;
	t_vector	normal;

	if (!(data[0] = get_interval(object, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(object, "<material>", "</material>"))
		|| !(data[3] = get_interval(object, "<normal>", "</normal>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_material(data[1], &args.material) == -1)
		|| (parsing_vector(data[3], &normal) == -1))
		return (NULL);
	data[2] = get_interval(object, "<physic>", "</physic>");
	parsing_physic(data[2], &args);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	return (new_plane(args, normal, 0));
}

t_sphere	*parsing_sphere(char *object)
{
	char		*data[4];
	t_objs_comp	args;
	double		radius;

	if (!(data[0] = get_interval(object, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(object, "<material>", "</material>"))
		|| !(data[3] = get_interval(object, "<radius>", "</radius>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_material(data[1], &args.material) == -1))
		return (NULL);
	data[2] = get_interval(object, "<physic>", "</physic>");
	parsing_physic(data[2], &args);
	radius = atod(data[3]);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	return (new_sphere(args, radius));
}

t_cylinder	*parsing_cylinder(char *object)
{
	char		*data[4];
	t_objs_comp	args;
	double		radius;

	if (!(data[0] = get_interval(object, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(object, "<material>", "</material>"))
		|| !(data[3] = get_interval(object, "<radius>", "</radius>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_material(data[1], &args.material) == -1))
		return (NULL);
	data[2] = get_interval(object, "<physic>", "</physic>");
	parsing_physic(data[2], &args);
	radius = atod(data[3]);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	return (new_cylinder(args, radius));
}

t_cone		*parsing_cone(char *object)
{
	char		*data[4];
	t_objs_comp	args;
	double		angle;

	if (!(data[0] = get_interval(object, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(object, "<material>", "</material>"))
		|| !(data[3] = get_interval(object, "<angle>", "</angle>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_material(data[1], &args.material) == -1))
		return (NULL);
	data[2] = get_interval(object, "<physic>", "</physic>");
	parsing_physic(data[2], &args);
	angle = atod(data[3]);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	return (new_cone(args, angle));
}
