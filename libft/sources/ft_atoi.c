/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:00:27 by fcecilie          #+#    #+#             */
/*   Updated: 2017/05/25 05:58:29 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	n;
	int neg;
	int zero;
	int result;

	n = 0;
	neg = 1;
	zero = 1;
	result = 0;
	while (str[n] == ' ' || str[n] == '\t' || str[n] == '\f' || str[n] == '\v'
			|| str[n] == '\r' || str[n] == '\n')
		n++;
	if (str[n] == '-' || str[n] == '+')
	{
		n++;
		if (str[n - 1] == '-')
			neg = -1;
	}
	while (str[n] != '\0' && '0' <= str[n] && str[n] <= '9')
	{
		result = (result * zero) + (str[n] - '0');
		zero = 10;
		n++;
	}
	return (result * neg);
}
