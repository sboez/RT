/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:23:55 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/27 10:49:14 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		n;
	char	*ptr;

	n = 0;
	if (!s || !f)
		return (NULL);
	if ((ptr = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))) == NULL)
		return (NULL);
	while (s[n])
	{
		ptr[n] = f(s[n]);
		n++;
	}
	ptr[n] = '\0';
	return (ptr);
}
