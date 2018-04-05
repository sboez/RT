/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 11:42:19 by shiro             #+#    #+#             */
/*   Updated: 2018/02/18 21:39:19 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H
# include "structures.h"

SDL_Color	get_text_color(t_dot pt, t_object *obj);
t_vector	get_map_vector(t_dot pt, t_object *obj);
Uint32		getpixel(SDL_Surface *surface, int x, int y, int *err);

#endif
