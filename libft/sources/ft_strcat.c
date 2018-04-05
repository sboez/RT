/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 10:50:29 by fcecilie          #+#    #+#             */
/*   Updated: 2017/03/10 22:50:22 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int len1;
	int len2;
	int n;

	n = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	while (n < len2)
	{
		s1[len1 + n] = s2[n];
		n++;
	}
	s1[len1 + n] = '\0';
	return (s1);
}
