/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:29 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/18 21:34:05 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "structures.h"

/*
** camera.c
*/
t_camera	new_camera(const t_dot origin, const t_dot angle,
						double field_of_view, double depth_of_field);
void		reset_camera(t_camera *cam);

/*
** view_plane.c
*/
void		view_plane(t_camera *cam);
void		view_plane_vector(int x, int y, t_camera *cam, t_vector *vd);

#endif
