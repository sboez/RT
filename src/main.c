/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:53:37 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/23 14:13:02 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <time.h>

int			force_exit(void)
{
	exit(1);
	return (0);
}

static void	init_list_evts(t_event **head, t_evt_data *data)
{
	new_event(head, SDL_KEYUP, data, &key_management);
	new_event(head, SDL_QUIT, NULL, &force_exit);
}

int			main_display(void *scene)
{
	t_scene	*scn;

	get_pxl_queue(get_sdl_core()->nb_threads);
	scn = (t_scene*)scene;
	if (scn->background)
		SDL_RenderCopy(get_sdl_core()->renderer, scn->background, NULL, NULL);
	view_plane(&scn->cam);
	scanning(scn);
	if (get_sdl_core()->aa)
	{
		antia();
		antia();
	}
	refresh_win(scn);
	return (1);
}

int			main(int ac, char **av)
{
	t_event		*events;
	t_evt_data	*data;
	t_scene		*scn;

	events = NULL;
	if (!(scn = parsing(ac, av)))
		ft_putendl("usage : ./rt file.xml");
	else
	{
		srand(time(NULL));
		srand48(time(NULL));
		data = new_evt_data(scn, SDL_CreateThread(main_display, "", scn));
		init_list_evts(&events, data);
		wait_events(events);
		SDL_WaitThread(data->running_thread, NULL);
		clear_events(&events);
		delete_scene(scn);
		delete_sdl_core();
	}
	exit(0);
}
