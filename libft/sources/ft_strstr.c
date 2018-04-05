/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:48:07 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/05 05:22:16 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int			n;
	int			d;
	const char	*occurence = NULL;

	n = 0;
	d = 0;
	if (little[0] == 0)
		return ((char*)(occurence = &big[n]));
	while (big[n] != '\0')
	{
		while (big[n + d] == little[d])
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
