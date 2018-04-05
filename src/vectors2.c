/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:45:00 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/17 18:33:16 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		vect_normalize(t_vector *v)
{
	double	len;

	len = get_vect_lenght(v);
	*v = (t_vector){v->x / len, v->y / len, v->z / len};
}

double		angle_between_vectors(t_vector a, t_vector b)
{
	double	angle;
	double	pdt_scalaire;
	double	dist_a;
	double	dist_b;

	dist_a = get_vect_lenght(&a);
	dist_b = get_vect_lenght(&b);
	if (!(dist_a && dist_b))
		return (0);
	pdt_scalaire = vect_dot_product(a, b);
	angle = acos(pdt_scalaire / (dist_a * dist_b)) * 180 / M_PI;
	return (angle);
}

t_vector	vector(double x, double y, double z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_dot		dot(double x, double y, double z)
{
	t_dot	d;

	d.x = x;
	d.y = y;
	d.z = z;
	return (d);
}

t_vector	vector_inv(t_vector v)
{
	return ((t_vector){-v.x, -v.y, -v.z});
}
