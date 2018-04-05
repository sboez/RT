/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 10:42:20 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/27 11:26:37 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strtrim_annexe(char const *s, int n, int d, int len)
{
	char	*ptr;

	ptr = NULL;
	while (s[n] == ' ' || s[n] == '\n' || s[n] == '\t')
		n++;
	if (s[n] == '\0')
	{
		if ((ptr = (char*)malloc(sizeof(char) * 1)) == NULL)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
		len--;
	if ((ptr = (char*)malloc(sizeof(char) * (len - n + 1))) == NULL)
		return (NULL);
	while (n < len)
	{
		ptr[d] = s[n];
		n++;
		d++;
	}
	ptr[d] = '\0';
	return (ptr);
}

char		*ft_strtrim(char const *s)
{
	int		n;
	int		d;
	int		len;
	char	*ptr;

	ptr = NULL;
	n = 0;
	d = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if ((ptr = ft_strtrim_annexe(s, n, d, len)) == NULL)
		return (NULL);
	else
		return (ptr);
}
