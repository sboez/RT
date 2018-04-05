/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:22:10 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/10 13:48:42 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	d;
	size_t	len1;

	d = 0;
	len1 = ft_strlen(s1);
	while (d < n && s2[d] != '\0')
	{
		s1[len1 + d] = s2[d];
		d++;
	}
	s1[len1 + d] = '\0';
	return (s1);
}
