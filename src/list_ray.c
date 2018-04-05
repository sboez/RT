/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 01:23:38 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/17 15:57:15 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_cell_ray(t_list_ray **head, t_ray *ray, double *dist, int i)
{
	t_list_ray	*tmp;

	if (ray->nb_intersect > 0 && gt(*dist, 0))
	{
		if (!(tmp = malloc(sizeof(t_list_ray))))
			exit_error("rt", "malloc");
		tmp->r = *ray;
		tmp->t = *dist;
		tmp->i = i;
		tmp->next = *head;
		*head = tmp;
	}
}

void	delete_cell_ray(t_list_ray **cell)
{
	t_list_ray	*tmp;

	tmp = *cell;
	*cell = (*cell)->next;
	free(tmp);
}
