/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:11:26 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/10 14:55:45 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			n;
	int			count_occurence;
	int			limit;

	n = 0;
	count_occurence = 0;
	limit = ft_strlen(s) + 1;
	while (n != limit)
	{
		if (s[n] == (unsigned char)c)
			count_occurence++;
		n++;
	}
	n = 0;
	while (n != limit)
	{
		if (s[n] == (unsigned char)c)
		{
			count_occurence--;
			if (count_occurence == 0)
				return ((char*)&s[n]);
		}
		n++;
	}
	return ((char*)(s = NULL));
}
