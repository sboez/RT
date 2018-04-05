/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:47:13 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/18 20:10:14 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "structures.h"

/*
** objects*.c
*/
void			delete_object(t_object *obj);
t_object		*new_object(t_type type, t_objs_comp args);
void			set_all_matrix(t_object *object, t_trans_data data);

/*
** box.c
*/
void			box_dependency_lists(t_box *box);
void			box_transform_planes(t_box *box, t_trans_data trs);
void			delete_box(t_box *box);
int				is_in_box_boundaries(const t_plane *p, t_box *b, t_dot *d);
t_box			*new_box(t_objs_comp args, t_dot size);

/*
** cone.c
*/
void			delete_cone(t_cone *cone);
t_cone			*new_cone(t_objs_comp args, double angle);

/*
** cylinder.c
*/
void			delete_cylinder(t_cylinder *cylinder);
t_cylinder		*new_cylinder(t_objs_comp args, double radius);

/*
** hyperboloid.c
*/
t_hyperboloid	*new_hyperboloid(t_objs_comp args, t_hyperboloid_args a);
void			delete_hyperboloid(t_hyperboloid *h);

/*
** plane.c
*/
void			delete_plane(t_plane *plane);
t_plane			*new_plane(t_objs_comp args, t_vector normal, int tgl);
double			plane_intersect(t_ray *ray, t_parequation e, t_object *obj,
								int i);

/*
** sphere.c
*/
void			delete_sphere(t_sphere *sphere);
t_sphere		*new_sphere(t_objs_comp args, double rad);

/*
** triangle.c
*/
void			delete_triangle(t_triangle	*triangle);
t_triangle		*new_triangle(t_objs_comp args, t_dot d_a, t_dot d_b,
							t_dot d_c);

#endif
