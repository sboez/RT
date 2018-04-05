/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 10:59:52 by shiro             #+#    #+#             */
/*   Updated: 2018/02/23 13:43:41 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_pxl_queue	**get_pxl_queue(int n)
{
	static t_pxl_queue	**queue = NULL;
	static int			nb_threads = 0;

	if (queue)
	{
		if (n <= nb_threads && n > 0)
			return (&queue[n - 1]);
		else
			return (NULL);
	}
	if (!(queue = malloc(n * sizeof(t_pxl_queue*))))
		exit_error("rt", "malloc");
	ft_bzero(queue, n * sizeof(t_pxl_queue*));
	nb_threads = n;
	return (queue);
}

void		delete_pxl_queues(void)
{
	int	i;

	i = 0;
	while (++i < get_sdl_core()->nb_threads)
		free(*get_pxl_queue(i));
	free(get_pxl_queue(0));
}

void		put_pixel(int x, int y, SDL_Color *color)
{
	if (color && color->a)
	{
		SDL_SetRenderDrawColor(get_sdl_core()->renderer, color->r, color->g,
							color->b, color->a);
		SDL_RenderDrawPoint(get_sdl_core()->renderer, x, y);
	}
}

static void	update_pxl_queue(t_pxl_queue **list_queue, int *nb_ended_threads,
							t_loadingbar *lb)
{
	int	i;
	int	rendered;

	i = -1;
	while (++i < get_sdl_core()->nb_threads)
	{
		rendered = list_queue[i]->rendered;
		if (!rendered)
		{
			lb->val++;
			put_pixel(list_queue[i]->x, list_queue[i]->y, &list_queue[i]->col);
			list_queue[i]->rendered = 1;
			if ((list_queue[i] + 1)->rendered >= -1)
				list_queue[i]++;
		}
		else if (rendered == -1)
		{
			(*nb_ended_threads)++;
			list_queue[i]->rendered = -3;
		}
		else if (rendered && rendered != -3 && !(list_queue[i] + 1)->rendered)
			list_queue[i]++;
	}
	update_loading_bar(lb);
}

int			rendering_thread(void *data)
{
	int				i;
	int				nb_ended_threads;
	t_pxl_queue		**list_queue;
	t_loadingbar	lb;

	(void)data;
	lb = new_loading_bar();
	if (!(list_queue = malloc(get_sdl_core()->nb_threads *
							sizeof(t_pxl_queue*))))
		exit_error("rt", "malloc");
	i = 0;
	while (++i <= get_sdl_core()->nb_threads)
		list_queue[i - 1] = *get_pxl_queue(i);
	nb_ended_threads = 0;
	while (nb_ended_threads != get_sdl_core()->nb_threads)
		update_pxl_queue(list_queue, &nb_ended_threads, &lb);
	free(list_queue);
	delete_pxl_queues();
	destroy_loading_bar(lb);
	return (0);
}
