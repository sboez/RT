/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:47:51 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/23 12:57:41 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		between(double value, double low_limit, double height_limit)
{
	if (value < low_limit || value > height_limit)
		return (-1);
	return (1);
}

double	atod(char *src)
{
	double	integer;
	double	decimal;
	char	*tmp;
	int		i;

	integer = abs(atoi(src));
	decimal = 0;
	if (ft_strchr(src, '.'))
	{
		i = 0;
		decimal = 1;
		ft_strncpy((tmp = ft_strnew(7)), ft_strchr(src, '.'), 7);
		while (*(tmp + (++i)))
			decimal *= 10;
		decimal = atoi(tmp + 1) / decimal;
		free(tmp);
	}
	return ((integer + decimal) * (*src == '-' ? -1 : 1));
}

int		get_status(char *status)
{
	if (ft_strcmp("empty", status) == 0)
		return (EMPTY);
	else if (ft_strcmp("full", status) == 0)
		return (FULL);
	else if (ft_strcmp("none", status) == 0)
		return (NONE);
	else
		return (-1);
}

void	free_tab(char **data, int size)
{
	while (--size > -1)
		free(data[size]);
}

void	init_tab(char **data, int size)
{
	while (--size > -1)
		data[size] = NULL;
}
