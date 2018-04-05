/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_bwnoise.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/18 20:42:17 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	apply_bwnoise(SDL_Surface *screen, int x, int y)
{
	SDL_Color		curr;
	unsigned char	n;

	while (y < get_sdl_core()->height)
	{
		while (x < get_sdl_core()->width)
		{
			curr = get_pixel_colors(screen, x, y);
			n = (unsigned char)rand();
			curr = (SDL_Color){(curr.r * 3 + n) / 4, (curr.g * 3 + n) / 4,
								(curr.b * 3 + n) / 4, 255};
			put_pixel(x, y, &curr);
			x++;
		}
		x = 0;
		y++;
	}
}

int		bwnoise(void)
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
	apply_bwnoise(screen, 0, 0);
	SDL_FreeSurface(screen);
	return (0);
}

char	*parsing_bwnoise(char *data, t_scene *scn, int *i)
{
	if (ft_strstr(data, "b&w noise") != data)
		return (data);
	scn->effects[++(*i)] = bwnoise;
	data += 9;
	while (*data && (ft_isspace(*data) || *data == ','))
		data++;
	return (data);
}
