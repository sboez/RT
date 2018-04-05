/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:03:51 by fcecilie          #+#    #+#             */
/*   Updated: 2017/06/28 01:24:33 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	n;

	n = ft_strlen(s);
	if ((ptr = (char*)malloc(sizeof(char) * (n + 1))) == NULL)
		return (NULL);
	n = 0;
	while (s[n] != '\0')
	{
		ptr[n] = s[n];
		n++;
	}
	ptr[n] = '\0';
	return (ptr);
}
