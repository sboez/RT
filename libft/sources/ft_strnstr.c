/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:31:36 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/07 17:12:16 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		n;
	size_t		d;
	const char	*occurence = NULL;

	n = 0;
	d = 0;
	if (little[0] == 0)
		return ((char*)(occurence = &big[n]));
	while (big[n] != '\0' && (n + d) < len)
	{
		while (big[n + d] == little[d] && (n + d) < len)
		{
			if (little[d + 1] == '\0')
				return ((char*)(occurence = &big[n]));
			d++;
		}
		d = 0;
		n++;
	}
	return ((char*)occurence);
}
