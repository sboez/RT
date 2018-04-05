/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/18 21:21:21 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_color(unsigned char a, unsigned char r, unsigned char v,
				unsigned char b)
{
	int color;

	color = (a * 16711680) + (r * 65536) + (v * 256) + b;
	return (color);
}

void	put_pixel32(SDL_Surface *surface, int x, int y, Uint32 colors)
{
	Uint32	*pixels;

	pixels = (Uint32*)surface->pixels;
	pixels[(y * surface->w) + x] = colors;
}
