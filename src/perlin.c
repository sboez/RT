/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/18 22:27:56 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rand_between(int min, int max)
{
	int i;

	if (min > max)
		return (min);
	i = (rand() % (max - min + 1)) + min;
	return (i);
}

int		randbet255(int r, int c, int val)
{
	if (c <= val || c < 1)
		r = (c + rand_between(0, val));
	else if (c >= 255 - val || c > 254)
		r = (c + rand_between(-val, 0));
	else
		r = (c + rand_between(-val, val));
	return (r);
}

void	perlinmaker(t_perlin *p, int x, int y)
{
	while (y < 1 && x < 512)
	{
		p->r = randbet255(p->r, p->r, p->size);
		p->tmp[x] = p->r;
		put_pixel32(p->perlin, x, y, set_color(255, p->r, p->r, p->r));
		x++;
	}
	while (x < 512)
	{
		if (x > 0 && x < 511)
			p->r = randbet255(p->r,
							(p->tmp[x] + p->tmp[x - 1] + p->tmp[x + 1]) / 3,
							p->size);
		else
			p->r = randbet255(p->r, p->tmp[x], p->size);
		p->tmp[x] = p->r;
		put_pixel32(p->perlin, x, y, set_color(255, p->r, p->r, p->r));
		x++;
	}
}

void	perlin_pinpin(int x, int y)
{
	t_perlin	p;

	p.r = rand_between(0, 255);
	p.size = 40;
	if ((p.perlin = SDL_CreateRGBSurface(0, 512, 512, 32, 0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	while (y < 512)
	{
		perlinmaker(&p, x, y);
		x = 0;
		y++;
	}
	if (SDL_SaveBMP(p.perlin, "perlin.bmp") != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
}
