/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_interval.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 02:24:44 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/17 16:30:38 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		clear_interval(char *src, const int start, const int len)
{
	int	n;

	n = 0;
	while (src[start + n] && n < len)
	{
		src[start + n] = ' ';
		n++;
	}
}

static int	get_order_of_apparition(const char *src, const char *s1,
									const char *s2)
{
	char	*str1;
	char	*str2;
	int		len1;
	int		len2;

	str1 = NULL;
	str2 = NULL;
	str1 = ft_strstr(src, s1);
	str2 = ft_strstr(src, s2);
	if (!(str1) && !(str2))
		return (0);
	if (str1 && !str2)
		return (1);
	if (str2 && !str1)
		return (2);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 > len2)
		return (1);
	else
		return (2);
}

static char	*get_order_buffer(const char *src, const char *start,
							const char *stop)
{
	char	*buffer;
	int		n;
	int		order;

	if (!(buffer = ft_memalloc(ft_strlen(src) + 1)))
		return (NULL);
	n = 0;
	while ((order = get_order_of_apparition(src, start, stop)))
	{
		buffer[n] = order + '0';
		if (order == 1)
			src = ft_strstr(src, start) + ft_strlen(start);
		if (order == 2)
			src = ft_strstr(src, stop) + ft_strlen(stop);
		n++;
	}
	if (n == 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[n] = '\0';
	return (buffer);
}

static char	*get_stop_ptr(const char *src, const char *buffer,
						const char *start, const char *stop)
{
	char	*ptr;
	int		lenght[2];
	int		status;
	int		n;

	status = -1;
	n = 0;
	lenght[0] = ft_strlen(start);
	lenght[1] = ft_strlen(stop);
	ptr = (char*)src;
	while (status && ++n)
	{
		status += (status == -1) ? 1 : 0;
		if (buffer[n - 1] == '1')
		{
			ptr = ft_strstr(ptr, start) + lenght[0];
			status++;
		}
		if (buffer[n - 1] == '2')
		{
			ptr = ft_strstr(ptr, stop) + lenght[1];
			status--;
		}
	}
	return (ptr);
}

char		*get_interval(char *s, const char *start, const char *stop)
{
	char	*dst;
	char	*buffer;
	char	*ptr_stop;
	char	*ptr_start;

	dst = NULL;
	if (s && ft_strcmp(s, "") && ft_strcmp(start, "") && ft_strcmp(stop, ""))
	{
		ptr_start = ft_strstr(s, start);
		ptr_stop = ft_strstr(s, stop);
		if (ptr_start && ptr_stop &&
			(buffer = get_order_buffer(s, start, stop)))
		{
			ptr_stop = get_stop_ptr(s, buffer, start, stop) - ft_strlen(stop);
			ptr_start = ft_strstr(s, start);
			if ((dst = ft_memalloc(ft_strlen(ptr_start + ft_strlen(start)) -
									ft_strlen(ptr_stop) + 1)))
			{
				dst = get_dst_norme(dst, ptr_start, ptr_stop, start);
				clear_interval_norme(s, ptr_start, ptr_stop, stop);
			}
			free(buffer);
		}
	}
	return (dst);
}
