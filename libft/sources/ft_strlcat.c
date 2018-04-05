/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:53:47 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/24 09:55:31 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_dst;
	size_t	n;
	size_t	d;
	size_t	size_src;

	size_dst = ft_strlen(dst);
	n = size_dst;
	d = 0;
	size_src = ft_strlen(src);
	while (n < size - 1 && src[d] != '\0')
	{
		dst[n] = src[d];
		n++;
		d++;
	}
	dst[n] = '\0';
	if (size_dst > size)
		return (size_src + size);
	return (size_dst + size_src);
}
