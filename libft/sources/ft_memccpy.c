/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 12:22:21 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/27 11:40:35 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			d;
	unsigned char	*dst2;
	unsigned char	*src2;

	d = 0;
	dst2 = (unsigned char*)dst;
	src2 = (unsigned char*)src;
	if (n == 0)
		return (NULL);
	while (d < n && src2[d] != (unsigned char)c)
	{
		dst2[d] = src2[d];
		d++;
	}
	if (src2[d] == (unsigned char)c)
	{
		dst2[d] = src2[d];
		return (&dst[d + 1]);
	}
	return (NULL);
}
