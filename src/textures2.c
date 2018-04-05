/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/18 19:45:51 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

void	spherical_mapping(t_dot i, t_dot *textel, double streching,
						SDL_Surface *texture)
{
	int	w;
	int	h;

	vect_normalize((t_vector*)&i);
	w = texture ? texture->w : 2;
	h = texture ? texture->h : 1;
	textel->x = 0.5 + ((atan2(-i.x, -i.z)) / (2 * M_PI));
	textel->y = (acos(i.y)) / (M_PI);
	textel->x *= w * streching;
	textel->y *= h * streching;
}

void	cylindrical_mapping(t_dot i, t_dot *textel, double streching,
							SDL_Surface *texture)
{
	int	w;
	int	h;

	w = texture ? texture->w : 2;
	h = texture ? texture->h : 1;
	vect_normalize((t_vector*)&i);
	textel->x = 0.5 + (atan2(-i.x, -i.z) / (2 * M_PI));
	textel->x *= w * streching;
	i.y /= sqrt(i.x * i.x + i.z * i.z);
	if (texture)
		textel->y = -i.y * h * (streching / (2 * M_PI));
	else
		textel->y = i.y * streching;
}

void	planar_mapping_x(t_dot i, t_dot *textel, double streching,
						SDL_Surface *texture)
{
	int	w;
	int	h;

	w = texture ? texture->w : 1;
	h = texture ? texture->h : 1;
	if (texture)
		*textel = (t_dot){i.z * w * (streching / (2 * M_PI)),
						-i.y * h * (streching / (2 * M_PI)), 0};
	else
		*textel = (t_dot){i.z * streching, i.y * streching, 0};
}

void	planar_mapping_y(t_dot i, t_dot *textel, double streching,
						SDL_Surface *texture)
{
	int	w;
	int	h;

	w = texture ? texture->w : 1;
	h = texture ? texture->h : 1;
	if (texture)
		*textel = (t_dot){i.x * w * (streching / (2 * M_PI)),
						-i.z * h * (streching / (2 * M_PI)), 0};
	else
		*textel = (t_dot){i.x * streching, i.z * streching, 0};
}

void	planar_mapping_z(t_dot i, t_dot *textel, double streching,
						SDL_Surface *texture)
{
	int	w;
	int	h;

	w = texture ? texture->w : 1;
	h = texture ? texture->h : 1;
	if (texture)
		*textel = (t_dot){i.y * w * (streching / (2 * M_PI)),
						-i.x * h * (streching / (2 * M_PI)), 0};
	else
		*textel = (t_dot){i.y * streching, i.x * streching, 0};
}
