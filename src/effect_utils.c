/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 21:57:04 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/18 22:01:30 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Color	get_pixel_colors(SDL_Surface *screen, int x, int y)
{
	SDL_Color	rgba;

	rgba = (SDL_Color){0, 0, 0, 0};
	SDL_GetRGBA(getpixel(screen, x, y, &(int){0}), screen->format, &rgba.r,
						&rgba.g, &rgba.b, &rgba.a);
	return (rgba);
}

SDL_Color	pixelaccess(SDL_Surface *s, int x, int y, SDL_Color curr)
{
	if (x - 1 < 0 || y - 1 < 0 || x + 1 > get_sdl_core()->width ||
		y + 1 > get_sdl_core()->height)
		return (curr);
	return (get_pixel_colors(s, x, y));
}
