/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 10:06:51 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/10 13:49:54 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t n;

	n = 0;
	while (src[n] != '\0' && n < len)
	{
		dst[n] = src[n];
		n++;
	}
	while (n < len)
	{
		dst[n] = '\0';
		n++;
	}
	return (dst);
}
