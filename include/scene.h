/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:39 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/17 18:48:50 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "structures.h"

/*
** scene.c
*/
void	delete_scene(t_scene *scene);
t_scene	*new_scene(t_camera cam, double brightness, SDL_Texture *bg);
t_scene	*parsing_scene(char *file);

/*
** scene_lights.c
*/
void	delete_cell_light(t_list_lights **cell);
void	new_cell_light(t_list_lights **head, t_light *light);

/*
** scene_objs.c
*/
void	delete_cell_obj(t_list_objs **cell);
void	new_cell_obj(t_list_objs **head, t_object *obj);

#endif
