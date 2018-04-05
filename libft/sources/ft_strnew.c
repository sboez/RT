/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 15:23:12 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/24 12:08:25 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*ptr;
	size_t	n;

	n = 0;
	ptr = (char*)malloc(sizeof(*ptr) * size + 1);
	if (ptr == NULL)
		return (NULL);
	while (n < size + 1)
	{
		ptr[n] = '\0';
		n++;
	}
	return (ptr);
}
