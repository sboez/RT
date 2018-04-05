/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 18:38:57 by shiro             #+#    #+#             */
/*   Updated: 2018/02/19 15:34:05 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H
# include "structures.h"

double	check_intersect(t_ray *ray, const t_list_objs *l, int check_lights,
						const t_object *filter);
t_ray	first_intersect(const t_ray *ray, t_object *obj, double *tmp);
int		is_in_limited_obj(const double *t, const t_ray *ray, t_object *obj);
int		is_in_obj(const double t, const t_dot inter, t_object *obj);
t_ray	second_intersect(const t_ray *ray, t_object *obj, double *tmp);

#endif
