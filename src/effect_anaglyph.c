/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_anaglyph.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/18 21:55:17 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	apply_anaglyph(SDL_Surface *screen, int x, int y)
{
	SDL_Color	curr;
	SDL_Color	r;

	while (y < get_sdl_core()->height)
	{
		while (x < get_sdl_core()->width)
		{
			curr = get_pixel_colors(screen, x - 15, y);
			r = get_pixel_colors(screen, x + 15, y);
			if (x < 15)
				curr = (SDL_Color){r.r, 0, 0, 255};
			if (x > get_sdl_core()->width - 15)
				curr = (SDL_Color){0, curr.g, curr.b, 255};
			else
				curr = (SDL_Color){r.r, curr.g, curr.b, 255};
			put_pixel(x, y, &curr);
			x++;
		}
		x = 0;
		y++;
	}
}

int		anaglyph(void)
{
	SDL_Surface	*screen;

	if ((screen = SDL_CreateRGBSurface(0, get_sdl_core()->width,
										get_sdl_core()->height, 32,
										0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	if (SDL_RenderReadPixels(get_sdl_core()->renderer, NULL,
							SDL_GetWindowPixelFormat(get_sdl_core()->window),
							screen->pixels, screen->pitch) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	apply_anaglyph(screen, 0, 0);
	SDL_FreeSurface(screen);
	return (0);
}

char	*parsing_anaglyph(char *data, t_scene *scn, int *i)
{
	if (ft_strstr(data, "anaglyph") != data)
		return (data);
	scn->effects[++(*i)] = anaglyph;
	data += 8;
	while (*data && (ft_isspace(*data) || *data == ','))
		data++;
	return (data);
}
