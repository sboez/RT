/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 12:21:27 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/18 22:09:44 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		new_event(t_event **head, SDL_EventType type, void *data,
					int (*fct)())
{
	t_event	*event;

	if (!(event = malloc(sizeof(t_event))))
		exit_error("RT", "malloc");
	*event = (t_event){type, data, fct, *head};
	*head = event;
}

void		clear_events(t_event **head)
{
	t_event	*tmp;

	while (*head)
	{
		tmp = *head;
		free(tmp->data);
		*head = (*head)->next;
		free(tmp);
	}
}

t_evt_data	*new_evt_data(t_scene *scn, SDL_Thread *t)
{
	t_evt_data	*data;

	if (!(data = malloc(sizeof(t_evt_data))))
		exit_error("rt", "malloc");
	data->scn = scn;
	data->running_thread = t;
	return (data);
}

void		wait_events(t_event *list_evts)
{
	SDL_Event	evt;
	t_event		*tmp;
	int			flag;

	flag = 1;
	while (flag)
	{
		tmp = list_evts;
		SDL_WaitEvent(&evt);
		while (tmp && tmp->type != evt.type)
			tmp = tmp->next;
		if (tmp)
			flag = tmp->fct(&evt, tmp);
	}
}
