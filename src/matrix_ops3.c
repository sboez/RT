/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 15:55:50 by shiro             #+#    #+#             */
/*   Updated: 2018/02/23 14:18:12 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

void		mult_vect(t_vector *dest, const t_matrix *mtx, const t_vector *vect)
{
	double	x;
	double	y;
	double	z;

	if (mtx->r >= 3 || mtx->c >= 4)
	{
		x = mtx->mat[0][0] * vect->x + mtx->mat[0][1] * vect->y +
			mtx->mat[0][2] * vect->z + mtx->mat[0][3];
		y = mtx->mat[1][0] * vect->x + mtx->mat[1][1] * vect->y +
			mtx->mat[1][2] * vect->z + mtx->mat[1][3];
		z = mtx->mat[2][0] * vect->x + mtx->mat[2][1] * vect->y +
			mtx->mat[2][2] * vect->z + mtx->mat[2][3];
		dest->x = x;
		dest->y = y;
		dest->z = z;
	}
}

t_matrix	*mult_matrix(t_matrix **res, t_matrix *m1, t_matrix *m2)
{
	int			r;
	int			c;
	int			i;
	t_matrix	*tmp;

	if (m1->c != m2->r || !res)
		return (NULL);
	if (!*res)
		*res = new_matrix(NULL, m1->r, m2->c);
	tmp = new_matrix(NULL, m1->r, m2->c);
	r = -1;
	while (++r < (*res)->r)
	{
		c = -1;
		while (++c < (*res)->c)
		{
			i = -1;
			while (++i < m1->c)
				tmp->mat[r][c] += m1->mat[r][i] * m2->mat[i][c];
		}
	}
	copy_matrix(*res, tmp);
	delete_matrix(tmp);
	return (*res);
}

t_matrix	*neg_matrix(t_matrix **res, t_matrix *m)
{
	int	i;
	int	j;

	if (!res)
		return (NULL);
	if (!*res)
		*res = new_matrix(NULL, m->r, m->c);
	i = -1;
	while (++i < m->r)
	{
		j = -1;
		while (++j < m->c)
			(*res)->mat[i][j] = -m->mat[i][j];
	}
	return (*res);
}
