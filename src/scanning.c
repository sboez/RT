/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/23 13:46:01 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	randomize_cam_orig(t_camera *cam)
{
	double	r;
	int		s;

	r = drand48();
	s = (int)(r * 10) % 2 ? -1 : 1;
	r = drand48();
	cam->origin.x += s * r * cam->depth;
	r = drand48();
	s = (int)(r * 10) % 2 ? -1 : 1;
	r = drand48();
	cam->origin.y += s * r * cam->depth;
	r = drand48();
	s = (int)(r * 10) % 2 ? -1 : 1;
	r = drand48();
	cam->origin.z += s * r * cam->depth;
}

static void	scan_pixel(t_ray *ray, t_thread_data *data, t_scanning_index *i)
{
	ray->equ.vc = (t_vector){data->scn.cam.origin.x, data->scn.cam.origin.y,
							data->scn.cam.origin.z};
	view_plane_vector(i->x, i->y, &data->scn.cam, &ray->equ.vd);
	effects(ray, &data->scn);
	(*get_pxl_queue(data->n_thread))[++i->q] = (t_pxl_queue){-2, i->x, i->y,
															ray->color};
	(*get_pxl_queue(data->n_thread))[i->q].rendered = 0;
}

static int	scanning_multi(void *data_void)
{
	t_thread_data		*data;
	t_scanning_index	i;
	t_ray				ray;
	t_dot				cam_orig;

	data = (t_thread_data *)data_void;
	cam_orig = data->scn.cam.origin;
	ray.actual_refractive_i = 1;
	ray.limit = LIMIT;
	ray.tree = add_new_leaf(NULL, NULL, NULL, 0);
	i.q = -1;
	i.y = data->y_begin;
	while (++i.y < data->y_end)
	{
		i.x = -1;
		while (++i.x < get_sdl_core()->width)
		{
			data->scn.cam.origin = cam_orig;
			randomize_cam_orig(&data->scn.cam);
			scan_pixel(&ray, data, &i);
		}
	}
	remove_leaf(ray.tree);
	return (0);
}

static void	print_time(t_time t)
{
	ft_putstr("total time: ");
	ft_putnbr(t.fin.time + (t.fin.millitm) / 1000.0 -
			t.debut.time - t.debut.millitm / 1000.0);
	ft_putstr("s\n");
}

void		scanning(t_scene *scn)
{
	t_thread_data	*threads;
	SDL_Thread		*rendering;
	int				i;
	t_time			t;

	threads = init_thread_array(scn, get_sdl_core()->nb_threads);
	i = -1;
	ftime(&t.debut);
	while (++i < get_sdl_core()->nb_threads)
		if (!(threads[i].thread = SDL_CreateThread(scanning_multi, "thread",
													(void*)&threads[i])))
			exit_custom_error("rt: SDL2: SDL_CreateThread: ",
							(char*)SDL_GetError());
	if (!(rendering = SDL_CreateThread(rendering_thread, "", NULL)))
		exit_custom_error("rt: SDL2: SDL_CreateThread: ",
						(char*)SDL_GetError());
	i = -1;
	while (++i < get_sdl_core()->nb_threads)
		SDL_WaitThread(threads[i].thread, NULL);
	SDL_WaitThread(rendering, NULL);
	free(threads);
	ftime(&t.fin);
	print_time(t);
}
