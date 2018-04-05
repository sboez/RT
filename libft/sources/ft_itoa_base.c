/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 01:15:12 by fcecilie          #+#    #+#             */
/*   Updated: 2017/05/04 03:54:07 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_nb(long long int n, int base)
{
	int count;

	if (n == 0)
		count = 1;
	else
		count = 0;
	while (n != 0)
	{
		n = n / base;
		count++;
	}
	return (count);
}

char		*ft_itoa_base(long long int n, int base, int maj)
{
	char			*str;
	int				count;
	int				neg;

	count = count_nb(n, base);
	if (!(str = (char *)ft_memalloc(sizeof(char) * (count + 1))))
		return (NULL);
	neg = (n < 0) ? -1 : 1;
	str[count] = '\0';
	while (count-- > 0)
	{
		if ((n % base) * neg < 10)
			str[count] = ((n % base) * neg) + '0';
		else
		{
			if (maj)
				str[count] = (((n % base) * neg) + 'A') - 10;
			if (!maj)
				str[count] = (((n % base) * neg) + 'a') - 10;
		}
		n = n / base;
	}
	return (str);
}
