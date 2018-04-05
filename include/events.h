/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:33 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/18 21:35:25 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H
# include "structures.h"
# include "key_functions.h"
# ifndef __APPLE__
#  include <SDL2/SDL.h>
# else
#  include <SDL2/SDL.h>
# endif

/*
** events.c
*/
void		clear_events(t_event **head);
void		delete_event(t_event **head);
void		new_event(t_event **head, SDL_EventType type, void *data,
					int (*fct)());
t_evt_data	*new_evt_data(t_scene *scn, SDL_Thread *t);
void		wait_events(t_event *list_evts);

#endif
