/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:32:58 by llellouc          #+#    #+#             */
/*   Updated: 2018/02/22 13:33:50 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_DATA_H
# define THREAD_DATA_H
# include "structures.h"

t_thread_data	*init_thread_array(t_scene *scn, int nb_thread);
t_mutexes		*get_mutexes();
void			destroy_mutexes();

#endif
