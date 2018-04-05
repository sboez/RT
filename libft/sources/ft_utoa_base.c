/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 01:15:12 by fcecilie          #+#    #+#             */
/*   Updated: 2017/05/04 01:05:17 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_nb(unsigned long long int n, int base)
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

char		*ft_utoa_base(unsigned long long int n, int base, int maj)
{
	char			*str;
	int				count;

	count = count_nb(n, base);
	if (!(str = (char *)ft_memalloc(sizeof(char) * (count + 1))))
		return (NULL);
	str[count] = '\0';
	while (count-- > 0)
	{
		if ((n % base) < 10)
			str[count] = ((n % base)) + '0';
		else
		{
			if (maj)
				str[count] = (((n % base)) + 'A') - 10;
			if (!maj)
				str[count] = (((n % base)) + 'a') - 10;
		}
		n = n / base;
	}
	return (str);
}
