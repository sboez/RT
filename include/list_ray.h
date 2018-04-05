/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ray.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 18:43:23 by shiro             #+#    #+#             */
/*   Updated: 2018/02/17 18:43:33 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_RAY_H
# define LIST_RAY_H
# include "structures.h"

void	add_cell_ray(t_list_ray **head, t_ray *ray, double *dist, int i);
void	delete_cell_ray(t_list_ray **cell);

#endif
