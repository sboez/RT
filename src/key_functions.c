/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 22:12:52 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/23 15:01:28 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	evt_antialiasing(t_evt_data *data)
{
	const int	w = WIN_WIDTH;
	const int	h = WIN_HEIGHT;

	SDL_WaitThread(data->running_thread, NULL);
	ft_putstr("\nLaunching antialiasing...\n");
	get_sdl_core()->width *= 4;
	get_sdl_core()->height *= 4;
	SDL_DestroyTexture(get_sdl_core()->target);
	get_sdl_core()->target = SDL_CreateTexture(get_sdl_core()->renderer,
												SDL_PIXELFORMAT_RGBA8888,
												SDL_TEXTUREACCESS_TARGET,
												w * 4, h * 4);
	SDL_SetRenderTarget(get_sdl_core()->renderer, get_sdl_core()->target);
	get_sdl_core()->aa = 1;
	reset_camera(&data->scn->cam);
	data->running_thread = SDL_CreateThread(main_display, "", data->scn);
}

static void	evt_screenshot(t_evt_data *data)
{
	SDL_WaitThread(data->running_thread, NULL);
	data->running_thread = NULL;
	screenshot();
	ft_putstr("\nScreenshot taken.\n");
}

int			key_management(SDL_Event *current, t_event *evt)
{
	t_evt_data	*data;

	data = evt->data;
	if (current->key.keysym.sym == SDLK_ESCAPE)
		return (0);
	else if (current->key.keysym.sym == SDLK_a && !get_sdl_core()->aa)
		evt_antialiasing(data);
	else if (current->key.keysym.sym == SDLK_s)
		evt_screenshot(data);
	return (1);
}
