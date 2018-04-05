/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 12:52:00 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/15 15:32:28 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H
# include "structures.h"

double		angle_between_vectors(t_vector a, t_vector b);
t_dot		dot(double x, double y, double z);
t_vector	dots_to_vect(t_dot d1, t_dot d2);
double		get_vect_lenght(const t_vector *vect);
double		get_dot_dist(const t_dot *d1, const t_dot *d2);
t_vector	vect_cross_product(const t_vector v1, const t_vector v2);
double		vect_dot_product(const t_vector v1, const t_vector v2);
void		vect_normalize(t_vector *v);
t_vector	vector(double x, double y, double z);
t_vector	vector_inv(t_vector	v);

#endif
