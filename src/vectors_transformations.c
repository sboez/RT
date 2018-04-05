/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_transformations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 15:41:16 by shiro             #+#    #+#             */
/*   Updated: 2018/02/17 18:31:50 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	vector_rotation_x(t_vector *v, double angle)
{
	t_vector	vec;

	vec = vector(v->x * 1 + v->y * 0 + v->z * 0,
				v->x * 0 + v->y * cos(angle) - v->z * sin(angle),
				v->x * 0 + v->y * sin(angle) + v->z * cos(angle));
	return (vec);
}

t_vector	vector_rotation_y(t_vector *v, double angle)
{
	t_vector	vec;

	vec = vector(v->x * cos(angle) + v->y * 0 + v->z * sin(angle),
				v->x * 0 + v->y * 1 + v->z * 0,
				-v->x * sin(angle) + v->y * 0 + v->z * cos(angle));
	return (vec);
}

t_vector	vector_rotation_z(t_vector *v, double angle)
{
	t_vector	vec;

	vec = vector(v->x * cos(angle) - v->y * sin(angle) + v->z * 0,
				v->x * sin(angle) + v->y * cos(angle) + v->z * 0,
				v->x * 0 + v->y * 0 + v->z * 1);
	return (vec);
}
