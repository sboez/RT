/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 02:40:37 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/31 02:48:48 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	a_b_exist(t_couple_ray *couple, t_ray *tmp, double *t_tmp)
{
	if (couple->ta < *t_tmp && *t_tmp < couple->tb)
		valid_ray(&couple->b, &couple->tb, tmp, t_tmp);
	else if (*t_tmp < couple->ta && *t_tmp < couple->tb)
	{
		valid_ray(&couple->b, &couple->tb, &couple->a, &couple->ta);
		valid_ray(&couple->a, &couple->ta, tmp, t_tmp);
	}
}

static void	a_exist(t_couple_ray *couple, t_ray *tmp, double *t_tmp)
{
	if (*t_tmp > couple->ta)
		valid_ray(&couple->b, &couple->tb, tmp, t_tmp);
	else
	{
		valid_ray(&couple->b, &couple->tb, &couple->a, &couple->ta);
		valid_ray(&couple->a, &couple->ta, tmp, t_tmp);
	}
}

static void	b_exist(t_couple_ray *couple, t_ray *tmp, double *t_tmp)
{
	if (*t_tmp < couple->tb)
		valid_ray(&couple->a, &couple->ta, tmp, t_tmp);
	else
	{
		valid_ray(&couple->a, &couple->ta, &couple->b, &couple->tb);
		valid_ray(&couple->b, &couple->tb, tmp, t_tmp);
	}
}

static void	no_one_exist(t_couple_ray *couple, t_ray *tmp, double *t_tmp)
{
	valid_ray(&couple->a, &couple->ta, tmp, t_tmp);
}

void		limit2(t_couple_ray *limited, t_ray *tmp, double *t_tmp)
{
	if (limited->a.nb_intersect > 0 && limited->b.nb_intersect > 0)
		a_b_exist(limited, tmp, t_tmp);
	else if (limited->a.nb_intersect > 0)
		a_exist(limited, tmp, t_tmp);
	else if (limited->b.nb_intersect > 0)
		b_exist(limited, tmp, t_tmp);
	else
		no_one_exist(limited, tmp, t_tmp);
}
