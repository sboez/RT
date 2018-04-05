/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:35:32 by shiro             #+#    #+#             */
/*   Updated: 2017/11/10 15:40:42 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_imin(int i1, int i2)
{
	return (i1 < i2 ? i1 : i2);
}

int		ft_imax(int i1, int i2)
{
	return (i1 > i2 ? i1 : i2);
}

double	ft_dmin(double d1, double d2)
{
	return (d1 < d2 ? d1 : d2);
}

double	ft_dmax(double d1, double d2)
{
	return (d1 > d2 ? d1 : d2);
}
