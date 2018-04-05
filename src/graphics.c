/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:52:28 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/23 10:57:52 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sdl_core	*get_sdl_core(void)
{
	static t_sdl_core	*core = NULL;

	if (core)
		return (core);
	if (!(core = malloc(sizeof(t_sdl_core))))
		exit_error("rt", "malloc");
	*core = (t_sdl_core){NULL, NULL, NULL, WIN_WIDTH, WIN_HEIGHT, 0, 0, 0};
	if (SDL_Init(SDL_VIDEO) ||
		!(core->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										WIN_WIDTH, WIN_HEIGHT,
										SDL_WINDOW_SHOWN)) ||
		!(core->renderer = SDL_CreateRenderer(core->window, -1,
											SDL_RENDERER_ACCELERATED |
											SDL_RENDERER_TARGETTEXTURE)))
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	core->target = SDL_CreateTexture(core->renderer, SDL_PIXELFORMAT_RGBA32,
									SDL_TEXTUREACCESS_TARGET,
									WIN_WIDTH, WIN_HEIGHT);
	SDL_SetRenderTarget(core->renderer, core->target);
	return (core);
}

void		delete_sdl_core(void)
{
	SDL_DestroyTexture(get_sdl_core()->target);
	SDL_DestroyRenderer(get_sdl_core()->renderer);
	SDL_DestroyWindow(get_sdl_core()->window);
	SDL_Quit();
	free(get_sdl_core());
}

static void	apply_effects(t_scene *scn)
{
	int	i;

	i = -1;
	while (scn->effects[++i])
		scn->effects[i](scn->dt_col1, scn->dt_col2);
}

void		refresh_win(t_scene *scn)
{
	SDL_SetRenderTarget(get_sdl_core()->renderer, NULL);
	SDL_RenderCopy(get_sdl_core()->renderer, get_sdl_core()->target,
					&((SDL_Rect){0, 0, WIN_WIDTH, WIN_HEIGHT}), NULL);
	apply_effects(scn);
	SDL_RenderPresent(get_sdl_core()->renderer);
	SDL_SetRenderTarget(get_sdl_core()->renderer, get_sdl_core()->target);
}

int			coloreq(SDL_Color c1, SDL_Color c2)
{
	return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}
