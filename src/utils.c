/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 11:25:07 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/17 18:30:23 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	gt(double nb1, double nb2)
{
	return ((long)(nb1 * POW) > (long)(nb2 * POW));
}

int	lt(double nb1, double nb2)
{
	return ((long)(nb1 * POW) < (long)(nb2 * POW));
}

int	ge(double nb1, double nb2)
{
	return ((long)(nb1 * POW) >= (long)(nb2 * POW));
}

int	le(double nb1, double nb2)
{
	return ((long)(nb1 * POW) <= (long)(nb2 * POW));
}

int	eq(double nb1, double nb2)
{
	return ((long)(nb1 * POW) == (long)(nb2 * POW));
}
