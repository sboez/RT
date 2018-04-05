/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 11:13:32 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/14 13:18:09 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int count;
	int div;

	count = ft_cnt_fgr(n);
	div = ft_div_nbr(n);
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = (n * -1);
	}
	while (count > 0)
	{
		ft_putchar((n / div) + '0');
		n = n % div;
		div = div / 10;
		count--;
	}
}
