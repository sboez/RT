/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 16:19:15 by fcecilie          #+#    #+#             */
/*   Updated: 2017/06/30 04:46:24 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *old, size_t add)
{
	char	*new;

	new = NULL;
	if (!(new = (char*)ft_memalloc(sizeof(char) * (ft_strlen(old) + add + 1))))
		return (NULL);
	if (old != NULL)
	{
		new = ft_strcpy(new, old);
		ft_memdel((void**)&old);
	}
	return (new);
}
