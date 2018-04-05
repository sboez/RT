/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:29:16 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/09 17:19:43 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t d;

	d = 0;
	if (n <= 0)
		return (0);
	while (s1[d] == s2[d] && d < n - 1 && s1[d] != '\0' && s2[d] != '\0')
		d++;
	return ((unsigned char)s1[d] - (unsigned char)s2[d]);
}
