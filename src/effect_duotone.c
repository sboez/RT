/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_duotone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/18 21:59:53 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		apply_duotone(SDL_Surface *screen, int x, int y, t_duotone t)
{
	SDL_Color curr;

	while (y < get_sdl_core()->height)
	{
		while (x < get_sdl_core()->width)
		{
			curr = get_pixel_colors(screen, x, y);
			curr.r = (curr.r * t.c1.r + (256 - curr.r) * t.c2.r) / 256;
			curr.g = (curr.g * t.c1.g + (256 - curr.g) * t.c2.g) / 256;
			curr.b = (curr.b * t.c1.b + (256 - curr.b) * t.c2.b) / 256;
			curr.a = 255;
			put_pixel(x, y, &curr);
			x++;
		}
		x = 0;
		y++;
	}
}

int			duotone(SDL_Color col1, SDL_Color col2)
{
	SDL_Surface			*screen;
	t_duotone			tones;

	tones = (t_duotone){col1, col2};
	if ((screen = SDL_CreateRGBSurface(0, get_sdl_core()->width,
										get_sdl_core()->height, 32,
										0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	if (SDL_RenderReadPixels(get_sdl_core()->renderer, NULL,
							SDL_GetWindowPixelFormat(get_sdl_core()->window),
							screen->pixels, screen->pitch) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	apply_duotone(screen, 0, 0, tones);
	SDL_FreeSurface(screen);
	return (0);
}

static char	*duo_tone_color(char *data, SDL_Color *col)
{
	col->r = ft_atoi(data);
	data = ft_strchr(data, '/');
	if (data && *data)
		data++;
	else
		return (NULL);
	col->g = ft_atoi(data);
	data = ft_strchr(data, '/');
	if (data && *data)
		data++;
	else
		return (NULL);
	col->b = ft_atoi(data);
	while (*data && (ft_isspace(*data) || ft_isdigit(*data) || *data == ','))
		data++;
	return (data);
}

char		*parsing_duotone(char *data, t_scene *scn, int *i)
{
	char	*tmp;

	if (ft_strstr(data, "duo tone:") != data)
		return (data);
	scn->effects[++(*i)] = duotone;
	data += 9;
	if (!(tmp = duo_tone_color(data, &scn->dt_col1)))
		return (data);
	else
		data = tmp;
	if (*data)
		data++;
	if (!(tmp = duo_tone_color(data, &scn->dt_col2)))
		return (data);
	else
		return (data);
}
