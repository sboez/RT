/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 13:05:58 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/19 16:01:20 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			d;
	unsigned char	*dst2;
	unsigned char	*src2;

	d = 0;
	dst2 = (unsigned char*)dst;
	src2 = (unsigned char*)src;
	if (dst > src && src2[d] != '\0' && dst2[d] != '\0')
	{
		while (len - 1 != 0 && src2[d] != '\0')
		{
			dst2[len - 1] = src2[len - 1];
			len--;
		}
		dst2[len - 1] = src2[len - 1];
	}
	else
		while (d < len && (src2[d] != '\0' || dst2[d] != '\0'))
		{
			dst2[d] = src2[d];
			d++;
		}
	return (dst);
}
