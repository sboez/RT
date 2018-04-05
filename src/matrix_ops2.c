/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 16:30:54 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/23 14:21:51 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double	**set_2x2mat_tab(double **dst, t_matrix *m, int i, int j)
{
	if (!dst)
	{
		dst = (double**)malloc(2 * sizeof(double*));
		dst[0] = (double*)malloc(2 * sizeof(double));
		dst[1] = (double*)malloc(2 * sizeof(double));
	}
	if (i < m->r && (i + 1) < m->r && j < m->c && (j + 1) < m->c)
	{
		dst[0][0] = m->mat[i][j];
		dst[0][1] = m->mat[i][j + 1];
		dst[1][0] = m->mat[i + 1][j];
		dst[1][1] = m->mat[i + 1][j + 1];
	}
	return (dst);
}

static void		set_2x2tab_mat(t_matrix *dst, double **tab, int i, int j)
{
	if (i < dst->r && (i + 1) < dst->r && j < dst->c && (j + 1) < dst->c)
	{
		dst->mat[i][j] = tab[0][0];
		dst->mat[i][j + 1] = tab[0][1];
		dst->mat[i + 1][j] = tab[1][0];
		dst->mat[i + 1][j + 1] = tab[1][1];
	}
}

static void		init_norme(t_la_norme_ce_putain_de_cancer *a, t_matrix *m)
{
	a->abcd[0] = new_matrix(set_2x2mat_tab(NULL, m, 0, 0), 2, 2);
	a->abcd[1] = new_matrix(set_2x2mat_tab(NULL, m, 0, 2), 2, 2);
	a->abcd[2] = new_matrix(set_2x2mat_tab(NULL, m, 2, 0), 2, 2);
	a->abcd[3] = new_matrix(set_2x2mat_tab(NULL, m, 2, 2), 2, 2);
	a->inv_a = NULL;
	a->inv_d = NULL;
	a->comp1 = NULL;
	a->comp2 = NULL;
}

static void		free_norme(t_la_norme_ce_putain_de_cancer *a)
{
	delete_matrix(a->abcd[0]);
	delete_matrix(a->abcd[1]);
	delete_matrix(a->abcd[2]);
	delete_matrix(a->abcd[3]);
	delete_matrix(a->r_abcd[0]);
	delete_matrix(a->r_abcd[1]);
	delete_matrix(a->r_abcd[2]);
	delete_matrix(a->r_abcd[3]);
	delete_matrix(a->inv_a);
	delete_matrix(a->inv_d);
}

t_matrix		*get_inv_4x4mat(t_matrix *res, t_matrix *m)
{
	t_la_norme_ce_putain_de_cancer	a;

	init_norme(&a, m);
	get_inv_2x2mat(&a.inv_a, a.abcd[0]);
	get_inv_2x2mat(&a.inv_d, a.abcd[3]);
	get_inv_2x2mat(&a.comp1, sub_matrix(&a.comp1, a.abcd[3],
				mult_matrix(&a.comp1, a.abcd[2],
							mult_matrix(&a.comp1, a.inv_a, a.abcd[1]))));
	get_inv_2x2mat(&a.comp2, sub_matrix(&a.comp2, a.abcd[0],
				mult_matrix(&a.comp2, a.abcd[1],
							mult_matrix(&a.comp2, a.inv_d, a.abcd[2]))));
	a.r_abcd[1] = NULL;
	a.r_abcd[2] = NULL;
	a.r_abcd[0] = a.comp2;
	neg_matrix(&a.r_abcd[1], mult_matrix(&a.r_abcd[1], a.inv_a,
								mult_matrix(&a.r_abcd[1], a.abcd[1], a.comp1)));
	neg_matrix(&a.r_abcd[2], mult_matrix(&a.r_abcd[2], a.comp1,
								mult_matrix(&a.r_abcd[2], a.abcd[2], a.inv_a)));
	a.r_abcd[3] = a.comp1;
	set_2x2tab_mat(res, a.r_abcd[0]->mat, 0, 0);
	set_2x2tab_mat(res, a.r_abcd[1]->mat, 0, 2);
	set_2x2tab_mat(res, a.r_abcd[2]->mat, 2, 0);
	set_2x2tab_mat(res, a.r_abcd[3]->mat, 2, 2);
	free_norme(&a);
	return (res);
}
