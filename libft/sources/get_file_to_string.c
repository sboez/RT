/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_to_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 00:57:00 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/23 15:00:17 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_file_to_string(int fd, char **file)
{
	char	*buf;
	int		readed;
	int		size;

	size = 0;
	readed = 0;
	if (!(buf = (char *)ft_memalloc(10000 + 1)))
		return (-1);
	while ((readed = read(fd, buf + size, 10000)) > 0)
	{
		size = size + readed;
		if (!(buf = ft_realloc(buf, readed)))
			return (-1);
	}
	if (readed < 0 || !(*file = ft_strdup(buf)))
		return (-1);
	ft_memdel((void**)&buf);
	return (0);
}
