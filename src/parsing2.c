/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:43:47 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/17 17:03:36 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	parsing_vector(char *data_vector, t_vector *d)
{
	char	*x;
	char	*y;
	char	*z;

	if (!(x = get_interval(data_vector, "<x>", "</x>"))
		|| !(y = get_interval(data_vector, "<y>", "</y>"))
		|| !(z = get_interval(data_vector, "<z>", "</z>")))
		return (-1);
	*d = vector(atod(x), atod(y), atod(z));
	free(x);
	free(y);
	free(z);
	return (0);
}

int	parsing_dot(char *data_dot, t_dot *d)
{
	char	*x;
	char	*y;
	char	*z;

	if (!(x = get_interval(data_dot, "<x>", "</x>"))
		|| !(y = get_interval(data_dot, "<y>", "</y>"))
		|| !(z = get_interval(data_dot, "<z>", "</z>")))
		return (-1);
	*d = dot(atod(x), atod(y), atod(z));
	free(x);
	free(y);
	free(z);
	return (0);
}
