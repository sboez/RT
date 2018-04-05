/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_transformations.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 18:49:50 by shiro             #+#    #+#             */
/*   Updated: 2018/02/17 18:49:50 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_TRANSFORMATIONS_H
# define VECTORS_TRANSFORMATIONS_H
# include "structures.h"

t_vector	vector_rotation_x(t_vector *v, double angle);
t_vector	vector_rotation_y(t_vector *v, double angle);
t_vector	vector_rotation_z(t_vector *v, double angle);

#endif
