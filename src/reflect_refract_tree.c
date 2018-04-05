/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect_refract_tree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 13:45:37 by shiro             #+#    #+#             */
/*   Updated: 2018/02/17 17:05:51 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_objs_tree	*add_new_leaf(t_objs_tree *root, t_objs_tree **branch,
						t_object *obj, int lvl)
{
	t_objs_tree	*new;

	if (!(new = malloc(sizeof(t_objs_tree))))
		exit_error("rt", "malloc");
	new->obj = obj;
	new->lvl = lvl;
	new->reflected = NULL;
	new->refracted = NULL;
	new->root = root;
	if (!root)
		return (new);
	if (branch)
		*branch = new;
	return (new);
}

t_objs_tree	*goto_root_obj(t_objs_tree *leaf, t_object *obj)
{
	while (leaf && leaf->obj != obj)
		leaf = leaf->root;
	while (leaf && leaf->root && leaf->root->obj == obj)
		leaf = leaf->root;
	return (leaf);
}

void		remove_leaf(t_objs_tree *leaf)
{
	if (leaf)
		free(leaf);
}
