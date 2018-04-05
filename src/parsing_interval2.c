/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_interval2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 15:34:48 by shiro             #+#    #+#             */
/*   Updated: 2018/02/17 15:36:23 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*get_dst_norme(char *dst, char *ptr_start, char *ptr_stop,
						const char *start)
{
	return (ft_strncpy(dst, ptr_start + ft_strlen(start),
				ft_strlen(ptr_start + ft_strlen(start)) - ft_strlen(ptr_stop)));
}

void	clear_interval_norme(char *src, char *ptr_start, char *ptr_stop,
							const char *stop)
{
	clear_interval(src, ft_strlen(src) - ft_strlen(ptr_start),
				ft_strlen(ptr_start) - ft_strlen(ptr_stop) + ft_strlen(stop));
}
