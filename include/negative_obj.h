/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 18:43:54 by shiro             #+#    #+#             */
/*   Updated: 2018/02/17 18:44:01 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEGATIVE_OBJ_H
# define NEGATIVE_OBJ_H
# include "structures.h"

void	negative_obj(t_list_ray **l_ray, t_couple_ray *basic, t_object *father,
					const t_ray *ray);

#endif
