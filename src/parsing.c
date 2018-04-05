/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:43:47 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/26 08:25:32 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parsing_physic(char *data_physic, t_objs_comp *args)
{
	char	*data[4];

	args->refraction_amount = 0;
	args->refractive_index = 0;
	args->reflection_amount = 0;
	args->shininess = 0;
	if ((data[0] = get_interval(data_physic,
								"<refraction_amount>", "</refraction_amount>"))
		&& between(args->refraction_amount = atod(data[0]), 0, 1) == -1)
		exit_custom_error("rt", ":refraction_amount must be between <0 - 1.0>");
	if ((data[1] = get_interval(data_physic,
								"<refraction_index>", "</refraction_index>")) &&
		args->refraction_amount != 0 &&
		(args->refractive_index = atod(data[1])) < 1)
		exit_custom_error("rt", ":refractive_index must be greater than <1>");
	if ((data[2] = get_interval(data_physic,
								"<reflexion_amount>", "</reflexion_amount>")) &&
		between(args->reflection_amount = atod(data[2]), 0, 1) == -1)
		exit_custom_error("rt", ":reflection_amount must be between <0 - 1.0>");
	if ((data[3] = get_interval(data_physic, "<shininess>", "</shininess>")) &&
		between(args->shininess = atod(data[3]), 0, 100) == -1)
		exit_custom_error("rt", ":shininess must be between <0 - 100>");
	free_tab(data, 4);
}

static void	parsing_threads(int ac, char **av)
{
	get_sdl_core()->nb_threads = (ac == 3 ? ft_atoi(av[2]) : 1);
	if (get_sdl_core()->nb_threads > WIN_HEIGHT)
		get_sdl_core()->nb_threads = WIN_HEIGHT;
	else if (get_sdl_core()->nb_threads < 1)
		exit_custom_error("rt", ":invalid number of threads");
}

t_scene		*parsing(int argc, char **argv)
{
	static t_scene	*scn = NULL;
	char			*file;
	char			*scene;
	int				fd;

	if ((argc == 2 || argc == 3) && argv[1] &&
		!ft_strcmp(ft_strstr(argv[1], ".xml"), ".xml"))
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			exit_custom_error("rt", ":open() failed");
		if (get_file_to_string(fd, &file) == -1)
			exit_custom_error("rt", ":get_file_to_string() failed");
		if (!(scene = get_interval(file, "<scene>", "</scene>")) ||
			!(scn = parsing_scene(scene)))
			exit_custom_error("rt", ":parsing_scene() failed");
		if (!(scn->lights = parsing_light(scene, &scn->objects)))
			ft_putstr_fd("\nWarning: no light found!\n", 2);
		if (!(scn->objects = parsing_object(scene, scn->objects)))
			ft_putstr_fd("\nWarning: no object found!\n", 2);
		close(fd);
		parsing_threads(argc, argv);
		free(scene);
		free(file);
	}
	return (scn);
}
