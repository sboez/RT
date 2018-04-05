/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_pop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/18 22:06:59 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_curr_norme(SDL_Color *curr, int x, int y)
{
	if (x <= get_sdl_core()->width / 2 && y <= get_sdl_core()->height / 2)
		*curr = (SDL_Color){255 - curr->r, curr->g, curr->b, 255};
	if (x > get_sdl_core()->width / 2 && y <= get_sdl_core()->height / 2)
		*curr = (SDL_Color){curr->r, 255 - curr->g, curr->b, 255};
	if (x <= get_sdl_core()->width / 2 && y > get_sdl_core()->height / 2)
		*curr = (SDL_Color){curr->r, curr->g, 255 - curr->b, 255};
	if (x > get_sdl_core()->width / 2 && y > get_sdl_core()->height / 2)
		*curr = (SDL_Color){255 - curr->r, curr->g, 255 - curr->b, 255};
}

void		apply_pop(SDL_Surface *screen, int x, int y)
{
	SDL_Color	curr;
	SDL_Color	b;

	while (y < get_sdl_core()->height)
	{
		while (x < get_sdl_core()->width)
		{
			curr = get_pixel_colors(screen, x, y);
			b = curr;
			curr = (SDL_Color){(b.r + b.g + b.b) / 3,
								(b.r + b.g + b.b) / 3,
								(b.r + b.g + b.b) / 3, 255};
			set_curr_norme(&curr, x, y);
			put_pixel(x, y, &curr);
			x++;
		}
		x = 0;
		y++;
	}
}

int			pop(void)
{
	SDL_Surface			*screen;

	if ((screen = SDL_CreateRGBSurface(0, get_sdl_core()->width,
										get_sdl_core()->height, 32,
										0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	if (SDL_RenderReadPixels(get_sdl_core()->renderer, NULL,
							SDL_GetWindowPixelFormat(get_sdl_core()->window),
							screen->pixels, screen->pitch) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	apply_pop(screen, 0, 0);
	return (0);
}

char		*parsing_pop(char *data, t_scene *scn, int *i)
{
	if (ft_strstr(data, "pop") != data)
		return (data);
	scn->effects[++(*i)] = pop;
	data += 3;
	while (*data && (ft_isspace(*data) || *data == ','))
		data++;
	return (data);
}
