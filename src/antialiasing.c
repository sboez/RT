/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/18 21:53:20 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Color	pixels_merger(SDL_Color pixel1, SDL_Color pixel2)
{
	pixel1 = (SDL_Color){(pixel1.r + pixel2.r) / 2, (pixel1.g + pixel2.g) / 2,
						(pixel1.b + pixel2.b) / 2, 255};
	return (pixel1);
}

void		x4_antia(SDL_Surface *screen, int x, int y)
{
	SDL_Color	pixel1;
	SDL_Color	pixel2;

	while (y < get_sdl_core()->height)
	{
		while (x < get_sdl_core()->width)
		{
			pixel1 = pixels_merger(get_pixel_colors(screen, x, y),
									get_pixel_colors(screen, x + 1, y));
			pixel2 = pixels_merger(get_pixel_colors(screen, x, y + 1),
									get_pixel_colors(screen, x + 1, y + 1));
			pixel1 = pixels_merger(pixel1, pixel2);
			put_pixel(x / 2, y / 2, &pixel1);
			x = x + 2;
		}
		x = 0;
		y = y + 2;
	}
}

int			antia(void)
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
	x4_antia(screen, 0, 0);
	return (0);
}
