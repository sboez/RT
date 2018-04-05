/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/23 14:54:08 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_loadingbar	new_loading_bar(void)
{
	t_loadingbar	lb;
	SDL_Surface		*tmp;

	lb = (t_loadingbar){NULL, 0, 0};
	tmp = NULL;
	if (!(tmp = SDL_LoadBMP("resources/loading.bmp")) ||
		!(lb.loadingtexture =
			SDL_CreateTextureFromSurface(get_sdl_core()->renderer, tmp)))
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	SDL_FreeSurface(tmp);
	return (lb);
}

void			destroy_loading_bar(t_loadingbar lb)
{
	SDL_DestroyTexture(lb.loadingtexture);
}

void			update_loading_bar(t_loadingbar *lb)
{
	SDL_Rect		dim;
	double			p;

	p = ((double)lb->val) / ((get_sdl_core()->width * get_sdl_core()->height));
	if (lb->val >= lb->old + LB)
	{
		lb->old = lb->val;
		dim = (SDL_Rect){0, WIN_HEIGHT - 20, WIN_WIDTH * p, 20};
		SDL_SetRenderDrawColor(get_sdl_core()->renderer, 180, 180, 180, 255);
		SDL_SetRenderTarget(get_sdl_core()->renderer, NULL);
		SDL_RenderCopy(get_sdl_core()->renderer, lb->loadingtexture, NULL,
					NULL);
		SDL_RenderFillRect(get_sdl_core()->renderer, &dim);
		SDL_RenderPresent(get_sdl_core()->renderer);
		SDL_SetRenderTarget(get_sdl_core()->renderer, get_sdl_core()->target);
	}
}
