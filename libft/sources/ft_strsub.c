/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:22:32 by fcecilie          #+#    #+#             */
/*   Updated: 2016/12/30 11:39:04 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	n;
	char	*ptr;

	n = 0;
	if (!s)
		return (NULL);
	if ((ptr = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (n < len)
	{
		ptr[n] = s[(size_t)start + n];
		n++;
	}
	ptr[len] = '\0';
	return (ptr);
}
