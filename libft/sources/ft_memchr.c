/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:08:01 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/27 11:39:17 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			d;
	unsigned char	*s2;

	s2 = (unsigned char*)s;
	d = 0;
	while (d < n && s2[d] != (unsigned char)c && s2[d] != '\0')
		d++;
	if (s2[d] == (unsigned char)c)
	{
		while (d != 0)
		{
			s++;
			d--;
		}
		return ((void*)s);
	}
	return (NULL);
}
