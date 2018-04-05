/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect_refract_tree.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:06:09 by shiro             #+#    #+#             */
/*   Updated: 2018/02/17 18:47:22 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFLECT_REFRACT_TREE_H
# define REFLECT_REFRACT_TREE_H
# include "structures.h"

/*
**	refract_list.c
*/
void		add_node(t_list_objs **l, t_object *obj);
void		remove_node(t_list_objs **l, t_object *obj);
int			if_node_exist(t_list_objs *l, t_object *obj);

/*
**reflect_refract_tree.c
*/
t_objs_tree	*add_new_leaf(t_objs_tree *root, t_objs_tree **branch,
						t_object *obj, int lvl);
t_objs_tree	*goto_root_obj(t_objs_tree *leaf, t_object *obj);
void		remove_leaf(t_objs_tree *leaf);

#endif
