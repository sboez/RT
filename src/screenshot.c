/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/19 17:07:56 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_access(const char *path)
{
	int	fd;

	fd = 0;
	if ((fd = open(path, O_RDONLY)) && fd == -1)
		return (-1);
	close(fd);
	return (0);
}

char	*screenshot_name(int num)
{
	char	*name;
	char	*numa;
	int		i;

	numa = ft_itoa(num);
	name = ft_strdup("Screenshot_0000.bmp");
	i = 0;
	while (numa[i])
	{
		name[15 - ft_strlen(numa) + i] = numa[i];
		i++;
	}
	free(numa);
	return (name);
}

char	*name_screen(void)
{
	int		z;
	char	*name;

	z = 1;
	while (z <= 9999)
	{
		name = screenshot_name(z);
		if (ft_access(name) == -1)
			return (name);
		else
			free(name);
		z++;
	}
	return (ft_strdup("Screenshot_MAX.bmp"));
}

int		screenshot(void)
{
	t_screenshot	s;

	s.winsize = (SDL_Rect){0, 0, WIN_WIDTH, WIN_HEIGHT};
	s.renderer = get_sdl_core()->renderer;
	if ((s.surface = SDL_CreateRGBSurface(0, WIN_WIDTH, WIN_HEIGHT, 32,
										0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	if (SDL_RenderReadPixels(s.renderer, &s.winsize,
							SDL_GetWindowPixelFormat(get_sdl_core()->window),
							s.surface->pixels, s.surface->pitch) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	s.name = name_screen();
	if (SDL_SaveBMP(s.surface, s.name) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	free(s.name);
	SDL_FreeSurface(s.surface);
	return (0);
}
