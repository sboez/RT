/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 15:30:54 by fcecilie          #+#    #+#             */
/*   Updated: 2017/05/31 06:07:48 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memcat(char *old, char *add)
{
	char	*new;

	new = ft_realloc(old, ft_strlen(add));
	new = ft_strcat(new, add);
	return (new);
}

int		read_next_line(int fd, t_line **cur)
{
	char	*buf;
	char	*tmp;
	int		ret;

	buf = (char*)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1));
	tmp = (char*)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1));
	if (buf == NULL || tmp == NULL)
		return (-1);
	while ((ft_memset(buf, '\0', ft_strlen(buf)))
		&& (ret = read(fd, buf, BUFF_SIZE)) && (ft_strchr(buf, '\n') == NULL))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		tmp = ft_memcat(tmp, buf);
	}
	buf[ret] = '\0';
	tmp = ft_memcat(tmp, buf);
	(*cur)->rest = ft_memcat((*cur)->rest, tmp);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&buf);
	return (ret);
}

int		search_t_line(int fd, t_line **first)
{
	while ((*first)->next != NULL && (*first)->fd != fd)
		(*first) = (*first)->next;
	if ((*first)->next == NULL && (*first)->fd != fd)
	{
		if (((*first)->next = (t_line*)ft_memalloc(sizeof(t_line))) == NULL)
			return (-1);
		(*first)->next->fd = fd;
		(*first)->next->rest = NULL;
		(*first)->next->next = NULL;
		(*first) = (*first)->next;
	}
	return (0);
}

int		parsing_line(char **line, t_line **cur, int ret)
{
	char	*tmp;
	int		check;
	int		len1;
	int		len2;

	len1 = ft_strnlen((*cur)->rest, '\n');
	len2 = ft_strlen((*cur)->rest + len1);
	check = 0;
	if ((*cur)->rest[0] == '\0' && ret == 0)
		check = 1;
	tmp = ft_strsub((*cur)->rest, (len1 + 1), (len2));
	*line = ft_strsub((*cur)->rest, 0, len1);
	ft_memdel((void**)&(*cur)->rest);
	(*cur)->rest = tmp;
	if (*line && check == 0)
		return (1);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_line	*current;
	t_line			*first_line;
	int				ret;

	if (fd < 0)
		return (-1);
	if (!current)
	{
		if ((current = (t_line*)ft_memalloc(sizeof(t_line) * (1))) == NULL)
			return (-1);
		current->fd = fd;
		current->rest = NULL;
		current->next = NULL;
	}
	first_line = current;
	if (search_t_line(fd, &current) == -1)
		return (-1);
	if ((ret = read_next_line(fd, &current)) == -1)
		return (-1);
	ret = parsing_line(line, &current, ret);
	current = first_line;
	return (ret);
}
