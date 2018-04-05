/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 12:05:12 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/24 11:30:54 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	d;
	char	*dst2;
	char	*src2;

	dst2 = NULL;
	src2 = NULL;
	dst2 = (char*)dst;
	src2 = (char*)src;
	d = 0;
	while (d < n)
	{
		dst2[d] = src2[d];
		d++;
	}
	return (dst);
}
