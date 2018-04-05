/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:36:36 by shiro             #+#    #+#             */
/*   Updated: 2018/02/18 19:05:02 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_dot	equation_get_dot(t_parequation *eq, double t)
{
	return ((t_dot){eq->vd.x * t + eq->vc.x,
					eq->vd.y * t + eq->vc.y,
					eq->vd.z * t + eq->vc.z});
}

int		get_quad_equation_sol(double *res, double fac[3], int i)
{
	double	delta;
	double	s1;
	double	s2;

	if (!fac[_A])
	{
		if (!fac[_B])
			return (0);
		*res = -fac[_C] / fac[_B];
		return (1);
	}
	if ((delta = (fac[_B] * fac[_B]) - (4 * fac[_A] * fac[_C])) < 0)
		return (0);
	s1 = (-fac[_B] - sqrt(delta)) / (2 * fac[_A]);
	s2 = (-fac[_B] + sqrt(delta)) / (2 * fac[_A]);
	if (lt(s1, 0) && lt(s2, 0))
		return (0);
	*res = (i == 1) ? ft_dmin(s1, s2) : ft_dmax(s1, s2);
	return (gt(s1, 0) + gt(s2, 0));
}
