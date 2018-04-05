/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 11:57:06 by fcecilie          #+#    #+#             */
/*   Updated: 2017/05/11 00:26:15 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_div_nbr(int n)
{
	int count;
	int div;

	count = 0;
	div = 1;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		count++;
	}
	while (count > 0)
	{
		div = div * 10;
		count--;
	}
	return (div);
}
