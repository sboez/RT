/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:41:24 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/18 22:28:22 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_scn_tab(t_scene *scn)
{
	int	i;

	i = -1;
	while (++i < 14)
		scn->effects[i] = NULL;
}

t_scene		*new_scene(t_camera cam, double brightness, SDL_Texture *bg)
{
	t_scene	*scene;

	if (!(scene = malloc(sizeof(t_scene))))
		exit_error("rtv1", "malloc");
	if (brightness > 100)
		brightness = 100;
	if (brightness < 0)
		brightness = 0;
	scene->brightness = brightness / 100;
	scene->cam = cam;
	scene->lights = NULL;
	scene->objects = NULL;
	scene->background = bg;
	scene->dt_col1 = (SDL_Color){0, 0, 0, 0};
	scene->dt_col2 = (SDL_Color){0, 0, 0, 0};
	init_scn_tab(scene);
	return (scene);
}

void		delete_scene(t_scene *scene)
{
	if (scene)
	{
		while (scene->objects)
			delete_cell_obj(&scene->objects);
		while (scene->lights)
			delete_cell_light(&scene->lights);
		SDL_DestroyTexture(scene->background);
		free(scene);
	}
}
