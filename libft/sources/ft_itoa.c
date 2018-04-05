/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:14:51 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/18 12:09:36 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		d;
	int		count;
	int		div;
	int		neg;
	char	*str;

	d = 0;
	count = ft_cnt_fgr(n);
	div = (n < 0) ? (ft_div_nbr(n) * -1) : ft_div_nbr(n);
	neg = (n < 0) ? 1 : 0;
	str = (char*)malloc(sizeof(char) * (count + 1 + neg));
	if (str == NULL)
		return (NULL);
	str[0] = (neg == 1) ? '-' : '\0';
	while (d < count)
	{
		str[d + neg] = (n / div) + '0';
		n = n % div;
		div = div / 10;
		d++;
	}
	str[d + neg] = '\0';
	return (str);
}
