/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 16:30:54 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/17 16:00:59 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

double		get_det_3x3mat(t_matrix *m)
{
	if (m->c < 3 || m->r < 3)
		return (0);
	return (m->mat[0][0] * m->mat[1][1] * m->mat[2][2] +
			m->mat[0][1] * m->mat[1][2] * m->mat[2][0] +
			m->mat[0][2] * m->mat[1][0] * m->mat[2][1] -
			m->mat[0][2] * m->mat[1][1] * m->mat[2][0] -
			m->mat[1][2] * m->mat[2][1] * m->mat[0][0] -
			m->mat[2][2] * m->mat[0][1] * m->mat[1][0]);
}

t_matrix	*get_inv_3x3mat(t_matrix *res, t_matrix *m)
{
	double			tmp[3][3];
	const double	d = get_det_3x3mat(m);
	int				i;
	int				j;

	if (!res)
		res = new_matrix(NULL, 3, 3);
	tmp[0][0] = (m->mat[1][1] * m->mat[2][2] - m->mat[1][2] * m->mat[2][1]) / d;
	tmp[0][1] = (m->mat[0][2] * m->mat[2][1] - m->mat[0][1] * m->mat[2][2]) / d;
	tmp[0][2] = (m->mat[0][1] * m->mat[1][2] - m->mat[0][2] * m->mat[1][1]) / d;
	tmp[1][0] = (m->mat[1][2] * m->mat[2][0] - m->mat[1][0] * m->mat[2][2]) / d;
	tmp[1][1] = (m->mat[0][0] * m->mat[2][2] - m->mat[0][2] * m->mat[2][0]) / d;
	tmp[1][2] = (m->mat[0][2] * m->mat[1][0] - m->mat[0][0] * m->mat[1][2]) / d;
	tmp[2][0] = (m->mat[1][0] * m->mat[2][1] - m->mat[1][1] * m->mat[2][0]) / d;
	tmp[2][1] = (m->mat[0][1] * m->mat[2][0] - m->mat[0][0] * m->mat[2][1]) / d;
	tmp[2][2] = (m->mat[0][0] * m->mat[1][1] - m->mat[0][1] * m->mat[1][0]) / d;
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			res->mat[i][j] = tmp[i][j];
	}
	return (res);
}

t_matrix	*sub_matrix(t_matrix **res, t_matrix *m1, t_matrix *m2)
{
	int	i;
	int	j;

	if (!res)
		return (NULL);
	if (!*res)
		*res = new_matrix(NULL, m1->r, m2->c);
	if (m1->r == m2->r && m1->c == m2->c)
	{
		i = -1;
		while (++i < m1->r)
		{
			j = -1;
			while (++j < m1->c)
				(*res)->mat[i][j] = m1->mat[i][j] - m2->mat[i][j];
		}
	}
	return (*res);
}

t_matrix	*add_matrix(t_matrix **res, t_matrix *m1, t_matrix *m2)
{
	int	i;
	int	j;

	if (!res)
		return (NULL);
	if (!*res)
		*res = new_matrix(NULL, m1->r, m2->c);
	if (m1->r == m2->r && m1->c == m2->c)
	{
		i = -1;
		while (++i < m1->r)
		{
			j = -1;
			while (++j < m1->c)
				(*res)->mat[i][j] = m1->mat[i][j] + m2->mat[i][j];
		}
	}
	return (*res);
}

t_matrix	*get_inv_2x2mat(t_matrix **res, t_matrix *m)
{
	double	tmp[2][2];
	double	d;

	if (!res ||
		!(d = (m->mat[0][0] * m->mat[1][1] - m->mat[0][1] * m->mat[1][0])))
		return (NULL);
	d = 1 / d;
	if (!*res)
		*res = new_matrix(NULL, m->r, m->c);
	tmp[0][0] = d * m->mat[1][1];
	tmp[0][1] = -d * m->mat[0][1];
	tmp[1][0] = -d * m->mat[1][0];
	tmp[1][1] = d * m->mat[0][0];
	(*res)->mat[0][0] = tmp[0][0];
	(*res)->mat[0][1] = tmp[0][1];
	(*res)->mat[1][0] = tmp[1][0];
	(*res)->mat[1][1] = tmp[1][1];
	return (*res);
}
