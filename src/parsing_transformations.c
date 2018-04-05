/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_transformations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 20:28:14 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/23 14:05:30 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parsing_transformations(t_object *obj, char *trans)
{
	char			*data[3];
	t_trans_data	trs;

	trs = (t_trans_data){(t_dot){0, 0, 0}, (t_dot){0, 0, 0}, (t_dot){1, 1, 1}};
	if (trans)
	{
		if ((data[0] = get_interval(trans, "<translation>", "</translation>"))
			&& parsing_dot(data[0], &trs.trans) == -1)
			exit_custom_error("rt", ":parsing translation failed");
		if ((data[1] = get_interval(trans, "<rotation>", "</rotation>")) &&
			parsing_dot(data[1], &trs.rot) == -1)
			exit_custom_error("rt", ":parsing rotation failed");
		if ((data[2] = get_interval(trans, "<scale>", "</scale>")) &&
			parsing_dot(data[2], &trs.scale) == -1)
			exit_custom_error("rt", ":parsing scale failed");
		if (trs.scale.x < 0 || trs.scale.y < 0 || trs.scale.z < 0)
			exit_custom_error("rt", ":scale must be greater than <0>");
		free(data[0]);
		free(data[1]);
		free(data[2]);
	}
	set_all_matrix(obj, trs);
	if (obj->obj_type == BOX)
		box_transform_planes((t_box*)obj, trs);
}
