/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:32:58 by llellouc          #+#    #+#             */
/*   Updated: 2018/02/23 11:17:39 by joinacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_thread_data	thread_data(int y_begin, int y_end, t_scene *scn,
									int n_thread)
{
	t_thread_data	ret;

	ret.y_begin = y_begin;
	ret.y_end = y_end;
	ret.scn = *scn;
	ret.n_thread = n_thread;
	return (ret);
}

static void				init_pxl_queue(t_thread_data *threads, int i)
{
	int			j;
	t_pxl_queue	**tmp;

	tmp = get_pxl_queue(i + 1);
	if (!((*tmp) = malloc(((threads[i].y_end - threads[i].y_begin - 1) *
						get_sdl_core()->width + 1) * sizeof(t_pxl_queue))))
		exit_error("rt", "malloc");
	j = -1;
	while (++j < (threads[i].y_end - threads[i].y_begin - 1) *
				get_sdl_core()->width)
		(*tmp)[j].rendered = -2;
	(*tmp)[j].rendered = -1;
}

t_thread_data			*init_thread_array(t_scene *scn, int nb_thread)
{
	t_thread_data	*threads;
	int				i;
	int				height_thread;

	if (!(threads = (t_thread_data*)malloc(sizeof(t_thread_data) * nb_thread)))
		exit_error("rt", "malloc");
	height_thread = get_sdl_core()->height / nb_thread;
	i = -1;
	while (++i < nb_thread - 1)
	{
		threads[i] = thread_data((height_thread * i) - 1,
								height_thread * (i + 1), scn, i + 1);
		init_pxl_queue(threads, i);
	}
	threads[i] = thread_data((height_thread * i) - 1,
							get_sdl_core()->height, scn, i + 1);
	init_pxl_queue(threads, i);
	return (threads);
}

t_mutexes				*get_mutexes(void)
{
	static t_mutexes	*mutex = NULL;

	if (!mutex)
	{
		if (!(mutex = malloc(sizeof(t_mutexes))))
			exit_error("rt", "malloc");
		if (!(mutex->loading_bar = SDL_CreateMutex()))
			exit_error("rt", "SDL_CreateMutex");
	}
	return (mutex);
}

void					destroy_mutexes(void)
{
	SDL_DestroyMutex(get_mutexes()->loading_bar);
	free(get_mutexes());
}
