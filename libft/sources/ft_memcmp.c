/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:44:04 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/10 13:45:34 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			d;
	unsigned char	*string1;
	unsigned char	*string2;

	d = 0;
	string1 = (unsigned char*)s1;
	string2 = (unsigned char*)s2;
	if (n == 0)
		return (0);
	while (string1[d] == string2[d] && d < n - 1)
		d++;
	return (string1[d] - string2[d]);
}
