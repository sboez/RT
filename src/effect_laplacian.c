/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_laplacian.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/18 22:01:07 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_blur	surrounding_pixels(SDL_Surface *screen, int x, int y)
{
	t_blur		b;
	SDL_Color	curr;

	curr = get_pixel_colors(screen, x, y);
	b = (t_blur){get_pixel_colors(screen, x - 1, y - 1),
				get_pixel_colors(screen, x + 1, y - 1),
				get_pixel_colors(screen, x - 1, y + 1),
				get_pixel_colors(screen, x + 1, y + 1),
				get_pixel_colors(screen, x, y - 1),
				get_pixel_colors(screen, x, y + 1),
				get_pixel_colors(screen, x - 1, y),
				get_pixel_colors(screen, x + 1, y), curr};
	return (b);
}

void	apply_laplacian(SDL_Surface *screen, int x, int y)
{
	SDL_Color	curr;
	t_blur		b;
	SDL_Surface	*screensav;

	screensav = screen;
	while (y < get_sdl_core()->height)
	{
		while (x < get_sdl_core()->width)
		{
			curr = get_pixel_colors(screen, x, y);
			b = surrounding_pixels(screensav, x, y);
			curr.r = curr.r * 4 - (b.tl1.r + b.tr1.r + b.bl1.r + b.br1.r);
			curr.g = curr.g * 4 - (b.tl1.g + b.tr1.g + b.bl1.g + b.br1.g);
			curr.b = curr.b * 4 - (b.tl1.b + b.tr1.b + b.bl1.b + b.br1.b);
			curr.a = 255;
			put_pixel(x, y, &curr);
			x++;
		}
		x = 0;
		y++;
	}
}

int		laplacian(void)
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
	apply_laplacian(screen, 0, 0);
	SDL_FreeSurface(screen);
	return (0);
}

char	*parsing_laplacian(char *data, t_scene *scn, int *i)
{
	if (ft_strstr(data, "laplacian") != data)
		return (data);
	scn->effects[++(*i)] = laplacian;
	data += 9;
	while (*data && (ft_isspace(*data) || *data == ','))
		data++;
	return (data);
}
