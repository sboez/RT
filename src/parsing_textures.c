/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:52:29 by shiro             #+#    #+#             */
/*   Updated: 2018/02/20 19:09:52 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "texture_mapping.h"

static int	parsing_mapping(char *mapping_method,
							void (**fct)(t_dot i, t_dot *textel,
										double streching, SDL_Surface *texture))
{
	if (ft_strequ(mapping_method, "spherical"))
		*fct = spherical_mapping;
	else if (ft_strequ(mapping_method, "cylindrical"))
		*fct = cylindrical_mapping;
	else if (ft_strequ(mapping_method, "planar"))
		*fct = planar_mapping;
	else
		return (-1);
	return (0);
}

static int	parsing_repeat(char *data, int *repeat)
{
	if (!ft_strequ(data, "true") && !ft_strequ(data, "false"))
		return (-1);
	*repeat = ft_strequ(data, "true");
	return (0);
}

int			parsing_texture(char *data_txt, t_obj_material *material)
{
	char	*tmp[5];

	if (!(tmp[0] = get_interval(data_txt, "<file>", "</file>")))
		return (-1);
	if (ft_strequ(tmp[0], "chess"))
		material->chess = 1;
	else if (!(material->texture = SDL_LoadBMP(tmp[0])))
		exit_custom_error("rt: SDL2: SDL_LoadBMP: ", (char*)SDL_GetError());
	if (!(tmp[1] = get_interval(data_txt, "<scale>", "</scale>")))
		return (-1);
	if (!(material->txt_streching = atod(tmp[1])))
		return (-1);
	if (!(tmp[2] = get_interval(data_txt, "<mapping>", "</mapping>")) ||
		parsing_mapping(tmp[2], &material->texture_mapping) == -1)
		return (-1);
	if (!(tmp[3] = get_interval(data_txt, "<transparency>", "</transparency>"))
		|| parsing_color(tmp[3], &material->transparent_color) == -1)
		material->transparency = 0;
	else
		material->transparency = 1;
	if (!(tmp[4] = get_interval(data_txt, "<repeat>", "</repeat>")) ||
		parsing_repeat(tmp[4], &material->txt_repeat) == -1)
		return (-1);
	free_tab(tmp, 5);
	return (0);
}

static int	parsing_normal_map_norme(char *tmp[4], char *data_map,
									t_obj_material *material)
{
	if (!(tmp[2] = get_interval(data_map, "<mapping>", "</mapping>")) &&
		!material->texture)
		return (-1);
	else if (!tmp[2] && material->texture)
		material->map_mapping = material->texture_mapping;
	else if (parsing_mapping(tmp[2], &material->map_mapping) == -1)
		return (-1);
	if (!(tmp[3] = get_interval(data_map, "<repeat>", "</repeat>")) &&
		!material->texture)
		return (-1);
	else if (!tmp[3] && material->texture)
		material->map_repeat = material->txt_repeat;
	else if (parsing_repeat(tmp[3], &material->map_repeat) == -1)
		return (-1);
	return (0);
}

int			parsing_normal_map(char *data_map, t_obj_material *material)
{
	char	*tmp[4];

	if (!(tmp[0] = get_interval(data_map, "<file>", "</file>")))
		return (-1);
	if (!(material->normal_map = SDL_LoadBMP(tmp[0])))
		exit_custom_error("rt: SDL2: SDL_LoadBMP: ", (char*)SDL_GetError());
	if (!(tmp[1] = get_interval(data_map, "<scale>", "</scale>")) &&
		!material->texture)
		return (-1);
	else if (!tmp[1] && material->texture)
		material->map_streching = material->txt_streching;
	else if (!(material->map_streching = atod(tmp[1])))
		return (-1);
	if (parsing_normal_map_norme(tmp, data_map, material) == -1)
		return (-1);
	free_tab(tmp, 4);
	return (0);
}
