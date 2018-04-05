/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_cartoon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/23 14:53:32 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	apply_cartoon(SDL_Surface *screen, SDL_Surface *cartoon, int x, int y)
{
	SDL_Color	curr;
	SDL_Color	tmp;

	while (y < get_sdl_core()->height)
	{
		while (x < get_sdl_core()->width)
		{
			curr = get_pixel_colors(screen, x, y);
			curr = (SDL_Color){(curr.r / 32) * 32,
								(curr.g / 32) * 32,
								(curr.b / 32) * 32, 255};
			tmp = get_pixel_colors(cartoon, x, y);
			curr.r = curr.r < tmp.r ? curr.r : tmp.r;
			curr.g = curr.g < tmp.g ? curr.g : tmp.g;
			curr.b = curr.b < tmp.b ? curr.b : tmp.b;
			put_pixel(x, y, &curr);
			x++;
		}
		x = 0;
		y++;
	}
}

int		cartoon(void)
{
	SDL_Surface	*screen;
	SDL_Surface	*cartoon;

	if ((screen = SDL_CreateRGBSurface(0, get_sdl_core()->width,
							get_sdl_core()->height, 32, 0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	if (SDL_RenderReadPixels(get_sdl_core()->renderer, NULL,
							SDL_GetWindowPixelFormat(get_sdl_core()->window),
							screen->pixels, screen->pitch) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	blur();
	gray();
	prewitt();
	negative();
	if ((cartoon = SDL_CreateRGBSurface(0, get_sdl_core()->width,
							get_sdl_core()->height, 32, 0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	if (SDL_RenderReadPixels(get_sdl_core()->renderer, NULL,
							SDL_GetWindowPixelFormat(get_sdl_core()->window),
							cartoon->pixels, cartoon->pitch) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	apply_cartoon(screen, cartoon, 0, 0);
	SDL_FreeSurface(cartoon);
	SDL_FreeSurface(screen);
	return (0);
}

char	*parsing_cartoon(char *data, t_scene *scn, int *i)
{
	if (ft_strstr(data, "cartoon") != data)
		return (data);
	scn->effects[++(*i)] = cartoon;
	data += 7;
	while (*data && (ft_isspace(*data) || *data == ','))
		data++;
	return (data);
}
