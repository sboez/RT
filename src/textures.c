/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/18 22:21:45 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "texture_mapping.h"
#include <math.h>

Uint32				getpixel(SDL_Surface *surface, int x, int y, int *err)
{
	int		bpp;
	Uint8	*p;

	if (x >= surface->w || y >= surface->h || x < 0 || y < 0)
	{
		*err = 1;
		return (0);
	}
	else
		*err = 0;
	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16 *)p);
	else if (bpp == 3)
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	else if (bpp == 4)
		return (*(Uint32 *)p);
	*err = 1;
	return (0);
}

void				planar_mapping(t_dot i, t_dot *textel, double streching,
									SDL_Surface *texture)
{
	planar_mapping_x(i, textel, streching, texture);
}

static SDL_Color	get_text_norme(t_object *obj, t_dot textel)
{
	Uint32		color;
	SDL_Color	ret;
	int			err;

	if (obj->material.txt_repeat)
		textel = (t_dot){mod(textel.x, obj->material.texture->w),
						mod(textel.y, obj->material.texture->h), 0};
	color = getpixel(obj->material.texture, textel.x, textel.y, &err);
	if (err)
		ret = obj->material.color;
	else
		SDL_GetRGB(color, obj->material.texture->format, &ret.r, &ret.g,
					&ret.b);
	return (ret);
}

SDL_Color			get_text_color(t_dot pt, t_object *obj)
{
	t_dot		textel;
	SDL_Color	ret;

	obj->material.texture_mapping(pt, &textel, obj->material.txt_streching,
								obj->material.texture);
	if (obj->material.texture)
		ret = get_text_norme(obj, textel);
	else
	{
		if ((textel.x < 0 && textel.y >= 0) || (textel.y <= 0 && textel.x > 0))
			ret = (mod(textel.x, 2) && !mod(textel.y, 2)) ||
				(!mod(textel.x, 2) && mod(textel.y, 2)) ?
					(SDL_Color){255, 255, 255, 255} : (SDL_Color){0, 0, 0, 255};
		else
			ret = (mod(textel.x, 2) && !mod(textel.y, 2)) ||
				(!mod(textel.x, 2) && mod(textel.y, 2)) ?
					(SDL_Color){0, 0, 0, 255} : (SDL_Color){255, 255, 255, 255};
	}
	ret.a = 255;
	return (ret);
}

t_vector			get_map_vector(t_dot pt, t_object *obj)
{
	t_dot		textel;
	SDL_Color	tmp;
	Uint32		color;
	int			err;

	obj->material.map_mapping(pt, &textel, obj->material.map_streching,
							obj->material.normal_map);
	if (obj->material.map_repeat)
		textel = (t_dot){mod(textel.x, obj->material.normal_map->w),
						mod(textel.y, obj->material.normal_map->h), 0};
	color = getpixel(obj->material.normal_map, textel.x, textel.y, &err);
	if (err)
		return ((t_vector){1, 1, 1});
	SDL_GetRGB(color, obj->material.normal_map->format, &tmp.r, &tmp.g, &tmp.b);
	return ((t_vector){((int)(tmp.r)) / 255.0, ((int)(tmp.g)) / 255.0,
						(((int)(tmp.b - 128))) / 255.0});
}
