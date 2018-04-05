/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:45:00 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/17 18:32:33 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_vector	dots_to_vect(t_dot d1, t_dot d2)
{
	return ((t_vector){d2.x - d1.x, d2.y - d1.y, d2.z - d1.z});
}

double		get_vect_lenght(const t_vector *vect)
{
	return (sqrt(vect->x * vect->x + vect->y * vect->y + vect->z * vect->z));
}

double		get_dot_dist(const t_dot *d1, const t_dot *d2)
{
	return (sqrt(pow(d2->x - d1->x, 2) + pow(d2->y - d1->y, 2) +
				pow(d2->z - d1->z, 2)));
}

double		vect_dot_product(const t_vector v1, const t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	vect_cross_product(const t_vector v1, const t_vector v2)
{
	return ((t_vector){v1.y * v2.z - v1.z * v2.y,
						v1.z * v2.x - v1.x * v2.z,
						v1.x * v2.y - v1.y * v2.x});
}
