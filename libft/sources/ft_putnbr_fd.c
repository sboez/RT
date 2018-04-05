/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:11:42 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/14 13:18:27 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int count;
	int div;

	count = ft_cnt_fgr(n);
	div = ft_div_nbr(n);
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = (n * -1);
	}
	while (count > 0)
	{
		ft_putchar_fd((n / div) + '0', fd);
		n = n % div;
		div = div / 10;
		count--;
	}
}
