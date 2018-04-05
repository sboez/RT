/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_gray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/18 22:00:18 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	apply_gray(SDL_Surface *screen, int x, int y)
{
	SDL_Color	curr;
	SDL_Color	c;

	while (y < get_sdl_core()->height)
	{
		while (x < get_sdl_core()->width)
		{
			curr = get_pixel_colors(screen, x, y);
			c = curr;
			curr = (SDL_Color){(c.r + c.g + c.b) / 3, (c.r + c.g + c.b) / 3,
								(c.r + c.g + c.b) / 3, 255};
			put_pixel(x, y, &curr);
			x++;
		}
		x = 0;
		y++;
	}
}

int		gray(void)
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
	apply_gray(screen, 0, 0);
	SDL_FreeSurface(screen);
	return (0);
}

char	*parsing_gray(char *data, t_scene *scn, int *i)
{
	if (ft_strstr(data, "desaturate") != data)
		return (data);
	scn->effects[++(*i)] = gray;
	data += 10;
	while (*data && (ft_isspace(*data) || *data == ','))
		data++;
	return (data);
}
