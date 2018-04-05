/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 10:57:01 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/17 17:22:43 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			get_refracted_vect(t_vector *dir, const t_vector *norm,
								double n1, double n2)
{
	double		cos_t[3];
	double		n1_n2;
	t_vector	u_dir;
	t_vector	u_norm;

	cos_t[1] = get_vect_lenght(dir);
	cos_t[2] = get_vect_lenght(norm);
	u_dir = vector(dir->x / cos_t[1], dir->y / cos_t[1], dir->z / cos_t[1]);
	u_norm = vector(norm->x / cos_t[2], norm->y / cos_t[2], norm->z / cos_t[2]);
	cos_t[1] = vect_dot_product(u_norm, vector_inv(u_dir));
	n1_n2 = n1 / n2;
	if ((cos_t[2] = (1 - pow(n1_n2, 2) * (1 - pow(cos_t[1], 2)))) < 0)
	{
		*dir = get_reflected_vect(dir, norm);
		return (1);
	}
	else
		cos_t[2] = sqrt(cos_t[2]);
	if (cos_t[1] > 0)
		cos_t[2] = -cos_t[2];
	dir->x = n1_n2 * u_dir.x + (n1_n2 * cos_t[1] + cos_t[2]) * u_norm.x;
	dir->y = n1_n2 * u_dir.y + (n1_n2 * cos_t[1] + cos_t[2]) * u_norm.y;
	dir->z = n1_n2 * u_dir.z + (n1_n2 * cos_t[1] + cos_t[2]) * u_norm.z;
	return (0);
}

void		get_refracted_col(t_ray *ray, t_object *src,
							SDL_Color refracted_obj_col)
{
	ray->color.r = (ray->color.r * (1 - src->obj_light.refraction_amount)) +
					(refracted_obj_col.r * src->obj_light.refraction_amount);
	ray->color.g = (ray->color.g * (1 - src->obj_light.refraction_amount)) +
					(refracted_obj_col.g * src->obj_light.refraction_amount);
	ray->color.b = (ray->color.b * (1 - src->obj_light.refraction_amount)) +
					(refracted_obj_col.b * src->obj_light.refraction_amount);
}

static void	update_tree_in(t_ray *ray, t_ray *ref_ray)
{
	int		t_ref;
	double	n1;
	double	n2;

	n1 = ray->tree->obj ? ray->tree->obj->obj_light.refractive_index : 1;
	n2 = ray->obj->obj_light.refractive_index;
	if (!(t_ref = get_refracted_vect(&ref_ray->equ.vd, &ray->normal, n1, n2)))
		ref_ray->tree = add_new_leaf(ray->tree, &ray->tree->refracted, ray->obj,
									ray->tree->lvl + 1);
	else
		ref_ray->tree = add_new_leaf(ray->tree, &ray->tree->refracted,
									ray->tree->obj, ray->tree->lvl);
}

static int	update_tree_out(t_ray *ray, t_ray *ref_ray)
{
	t_objs_tree	*first;
	int			t_ref;
	double		n1;
	double		n2;

	n1 = ray->tree->obj ? ray->tree->obj->obj_light.refractive_index : 1;
	n2 = ray->obj->obj_light.refractive_index;
	if (!(first = goto_root_obj(ray->tree, ray->obj)))
		first = goto_root_obj(ray->tree, ray->tree->obj);
	if (!first->root)
		return (0);
	if (first->lvl >= ray->tree->lvl)
		n2 = first->root->obj ? first->root->obj->obj_light.refractive_index :
								1;
	if (!(t_ref = get_refracted_vect(&ref_ray->equ.vd, &ray->normal, n1, n2)))
		ref_ray->tree = (first->lvl < ray->tree->lvl) ?
			add_new_leaf(first->root, NULL, ray->tree->obj, ray->tree->lvl) :
			add_new_leaf(first->root, NULL, first->root->obj, first->root->lvl);
	else
		ref_ray->tree = add_new_leaf(ray->tree, &ray->tree->refracted, ray->obj,
									ray->tree->lvl);
	return (1);
}

SDL_Color	refract(t_ray *ray, t_scene *scn)
{
	t_ray		ref_ray;
	SDL_Color	ret;

	ref_ray = *ray;
	if (ray->obj->obj_light.refraction_amount == 0)
		return (ref_ray.color);
	if (ray->limit < 0.1)
		return ((SDL_Color){0, 0, 0, 255});
	ref_ray.limit -= (1 - ray->obj->obj_light.refraction_amount) / 100;
	if (ray->nb_intersect == 2)
		update_tree_in(ray, &ref_ray);
	else if (!(update_tree_out(ray, &ref_ray)))
		return ((SDL_Color){0, 0, 0, 255});
	ref_ray.equ.vc = vector(ray->inter.x + (1 / POW) * ray->equ.vd.x,
							ray->inter.y + (1 / POW) * ray->equ.vd.y,
							ray->inter.z + (1 / POW) * ray->equ.vd.z);
	ret = effects(&ref_ray, scn);
	remove_leaf(ref_ray.tree);
	return (ret);
}
