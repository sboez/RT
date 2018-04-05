/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:47:13 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/23 12:53:15 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "structures.h"

/*
**	parsing.c
*/
t_scene				*parsing(int argc, char **argv);
int					parsing_dot(char *data_dot, t_dot *d);
void				parsing_physic(char *data_physic, t_objs_comp *args);
int					parsing_vector(char *data_vector, t_vector *d);

/*
**	parsing_textures.c
*/
int					parsing_color(char *data_color, SDL_Color *c);
int					parsing_material(char *data_mat, t_obj_material *material);
int					parsing_texture(char *data_txt, t_obj_material *material);
int					parsing_normal_map(char *data_map,
										t_obj_material *material);

/*
**	parsing_tools.c
*/
double				atod(char *src);
int					between(double value, double low_limit,
							double height_limit);
int					get_status(char *status);
void				free_tab(char **data, int size);
void				init_tab(char **data, int size);

/*
**	parsing_interval.c
*/
void				clear_interval(char *src, const int start, const int len);
char				*get_interval(char *src, const char *start,
								const char *stop);
char				*get_dst_norme(char *dst, char *ptr_start, char *ptr_stop,
									const char *start);
void				clear_interval_norme(char *src, char *ptr_start,
										char *ptr_stop, const char *stop);

/*
**	parsing_scene.c
*/
t_scene				*parsing_scene(char *scene);

/*
**	parsing_camera.c
*/
int					parsing_camera(char *scene, t_camera *cam);

/*
**	parsing_lights.c
*/
t_list_lights		*parsing_light(char *scene, t_list_objs **l_objs);
t_orb_light			*parsing_orb_light(char *light);
t_parallel_light	*parsing_parallel_light(char *light);
t_obj_light			*parsing_obj_light(char *light, t_list_lights **l);
t_spotlight			*parsing_spotlight(char *light);

/*
**	parsing_objects.c
*/
t_box				*parsing_box(char *object);
t_cone				*parsing_cone(char *object);
t_cylinder			*parsing_cylinder(char *object);
t_plane				*parsing_plane(char *object);
t_sphere			*parsing_sphere(char *object);
t_triangle			*parsing_triangle(char *object);
t_hyperboloid		*parsing_hyperboloid(char *object);
t_list_objs			*parsing_object(char *scene, t_list_objs *l);
t_object			*parsing_object2(char *object, int obj_light);

/*
**	parsing_transformations.c
*/
void				parsing_transformations(t_object *obj, char *trans);

/*
**	parsing_limit.c
*/
void				parsing_limit(t_object *obj, char *object);

/*
**	parsing_negative_obj.c
*/
void				parsing_negative_obj(t_object *obj, char *object);

#endif
