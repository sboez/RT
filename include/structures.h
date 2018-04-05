/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:19:46 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/23 11:21:30 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# ifndef __APPLE__
#  include <SDL2/SDL.h>
# else
#  include "SDL2/SDL.h"
# endif
# include <time.h>
# include <sys/timeb.h>

typedef struct				s_mutexes
{
	SDL_mutex				*loading_bar;
}							t_mutexes;

typedef struct				s_pxl_queue
{
	int						rendered;
	int						x;
	int						y;
	SDL_Color				col;
}							t_pxl_queue;

typedef struct				s_scanning_index
{
	int						x;
	int						y;
	int						q;
}							t_scanning_index;

typedef struct				s_sdl_core
{
	SDL_Window				*window;
	SDL_Renderer			*renderer;
	SDL_Texture				*target;
	int						width;
	int						height;
	int						nb_threads;
	int						fullscreen;
	int						aa;

}							t_sdl_core;

typedef struct				s_event
{
	SDL_EventType			type;
	void					*data;
	int						(*fct)();
	struct s_event			*next;
}							t_event;

typedef struct				s_evt_data
{
	struct s_scene			*scn;
	SDL_Thread				*running_thread;
}							t_evt_data;

typedef struct				s_time
{
	struct timeb			debut;
	struct timeb			fin;
}							t_time;

typedef struct				s_matrix
{
	double					**mat;
	int						r;
	int						c;
}							t_matrix;

typedef struct				s_la_norme_ce_putain_de_cancer
{
	t_matrix				*abcd[4];
	t_matrix				*r_abcd[4];
	t_matrix				*inv_a;
	t_matrix				*inv_d;
	t_matrix				*comp1;
	t_matrix				*comp2;
}							t_la_norme_ce_putain_de_cancer;

typedef struct				s_saloperie_de_norme_de_merde
{
	double					shade;
	double					opacity;
}							t_saloperie_de_norme_de_merde;

typedef struct				s_vector
{
	double					x;
	double					y;
	double					z;
}							t_vector;

typedef struct				s_dot
{
	double					x;
	double					y;
	double					z;
}							t_dot;

typedef struct				s_trans_data
{
	t_dot					trans;
	t_dot					rot;
	t_dot					scale;
}							t_trans_data;

typedef struct				s_parequation
{
	t_vector				vc;
	t_vector				vd;
}							t_parequation;

typedef struct				s_ray
{
	t_parequation			equ;
	t_dot					inter;
	t_vector				normal;
	SDL_Color				color;
	struct s_object			*obj;
	struct s_light			*light;
	struct s_objs_tree		*tree;
	double					shad_opacity;
	double					actual_refractive_i;
	double					percuted_refractive_i;
	double					limit;
	int						nb_intersect;
	int						i_intersect;
}							t_ray;

typedef struct				s_couple_ray
{
	t_ray					a;
	t_ray					b;
	double					ta;
	double					tb;
}							t_couple_ray;

typedef struct				s_list_ray
{
	t_ray					r;
	double					t;
	int						i;
	struct s_list_ray		*next;
}							t_list_ray;

typedef enum				e_type
{
	BOX,
	CONE,
	CYLINDER,
	HYPERBOLOID,
	PLANE,
	SPHERE,
	TRIANGLE
}							t_type;

typedef struct				s_obj_phys
{
	double					reflection_amount;
	double					refraction_amount;
	double					refractive_index;
	double					shininess;
}							t_obj_phys;

typedef struct				s_obj_material
{
	SDL_Color				color;
	SDL_Color				transparent_color;
	SDL_Surface				*texture;
	SDL_Surface				*normal_map;
	int						chess;
	int						transparency;
	int						txt_repeat;
	int						map_repeat;
	double					txt_streching;
	double					map_streching;
	void					(*texture_mapping)(t_dot i, t_dot *textel,
												double streching,
												SDL_Surface *texture);
	void					(*map_mapping)(t_dot i, t_dot *textel,
											double streching,
											SDL_Surface *texture);
}							t_obj_material;

typedef struct				s_object
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e,
										struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	t_obj_phys				obj_light;
	t_obj_material			material;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;
}							t_object;

typedef struct				s_objs_comp
{
	t_dot					orig;
	t_obj_material			material;
	double					reflection_amount;
	double					refraction_amount;
	double					refractive_index;
	double					shininess;
}							t_objs_comp;

typedef struct				s_sphere
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e,
										struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	t_obj_phys				obj_light;
	t_obj_material			material;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	double					radius;
	double					r2;
}							t_sphere;

typedef struct				s_cylinder
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e,
										struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	t_obj_phys				obj_light;
	t_obj_material			material;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	double					radius;
	double					r2;
}							t_cylinder;

typedef struct				s_cone
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e,
										struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	t_obj_phys				obj_light;
	t_obj_material			material;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	int						upper;
	double					angle;
	double					tanalpha2;
}							t_cone;

typedef struct				s_plane
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e,
										struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	t_obj_phys				obj_light;
	t_obj_material			material;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	t_vector				normal;
	double					a;
	double					b;
	double					c;
	double					d;
	double					z;
}							t_plane;

/*
** t_triangle hérite de plane puisque les calculs se ressemblent bcp
*/
typedef struct				s_triangle
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e,
										struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	t_obj_phys				obj_light;
	t_obj_material			material;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	t_vector				normal;
	double					a;
	double					b;
	double					c;
	double					d;
	double					z;
	double					a_a;
	double					a_b;
	t_dot					d_a;
	t_dot					d_b;
	t_dot					d_c;
	t_vector				v_ab;
	t_vector				v_ba;
	t_vector				v_bc;
}							t_triangle;

typedef struct				s_box
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e,
										struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	t_obj_phys				obj_light;
	t_obj_material			material;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	t_dot					size;
	t_dot					fbl_corner;
	t_dot					btr_corner;
	t_plane					*front;
	t_plane					*back;
	t_plane					*top;
	t_plane					*bottom;
	t_plane					*left;
	t_plane					*right;
}							t_box;

typedef struct				s_box_intersect
{
	t_box					*box;
	t_dot					inter;
	int						i;
	double					t;
	t_plane					*p;
}							t_box_intersect;

typedef struct				s_hyperboloid_args
{
	double					a;
	double					b;
	double					c;
	double					d;
}							t_hyperboloid_args;

typedef struct				s_hyperboloid
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e,
										struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	t_obj_phys				obj_light;
	t_obj_material			material;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	t_vector				normal;
	double					a2;
	double					b2;
	double					c2;
	double					d;
}							t_hyperboloid;

typedef enum				e_light_type
{
	OBJECT,
	ORB,
	PARALLEL,
	SPOT
}							t_light_type;

typedef struct				s_light_crd
{
	t_dot					orig;
	t_vector				direction;
}							t_light_crd;

typedef struct				s_light
{
	const t_light_type		type;
	SDL_Color				color;
	t_vector				direction;
	t_vector				(*get_ray_vect)(t_dot pos, struct s_light *light);
	int						(*is_in_light)(struct s_light *light,
										t_ray *light_ray);
	double					power;
}							t_light;

/*
** parallel_light hérite de light
*/
typedef struct				s_parallel_light
{
	const t_light_type		type;
	SDL_Color				color;
	t_vector				direction;
	t_vector				(*get_ray_vect)(t_dot pos, t_light *light);
	int						(*is_in_light)(t_light *light, t_ray *light_ray);
	double					power;
}							t_parallel_light;

/*
** spotlight hérite de light
*/
typedef struct				s_spotlight
{
	const t_light_type		type;
	SDL_Color				color;
	t_vector				direction;
	t_vector				(*get_ray_vect)(t_dot pos, t_light *light);
	int						(*is_in_light)(t_light *light, t_ray *light_ray);
	double					power;

	t_dot					orig;
	double					aperture;
}							t_spotlight;

/*
** orb_light hérite de spotlight
*/
typedef struct				s_orb_light
{
	const t_light_type		type;
	SDL_Color				color;
	t_vector				direction;
	t_vector				(*get_ray_vect)(t_dot pos, t_light *light);
	int						(*is_in_light)(t_light *light, t_ray *light_ray);
	double					power;

	t_dot					orig;
	double					aperture;
}							t_orb_light;

typedef struct				s_obj_light
{
	const t_light_type		type;
	SDL_Color				color;
	t_vector				direction;
	t_vector				(*get_ray_vect)(t_dot pos, struct s_light *light);
	int						(*is_in_light)(t_light *light, t_ray *light_ray);
	double					power;

	t_object				*shape;
}							t_obj_light;

typedef struct				s_view_plane
{
	t_dot					up_left;
	t_vector				front;
	t_vector				up;
	t_vector				right;
	t_vector				size;
}							t_view_plane;

typedef struct				s_camera
{
	t_dot					origin;
	t_dot					angle;
	double					depth;
	double					focal;
	double					fov;
	t_view_plane			vp;
}							t_camera;

typedef struct				s_list_objs
{
	t_object				*obj;
	struct s_list_objs		*next;
}							t_list_objs;

typedef struct				s_objs_tree
{
	t_object				*obj;
	int						lvl;
	struct s_objs_tree		*root;
	struct s_objs_tree		*reflected;
	struct s_objs_tree		*refracted;
}							t_objs_tree;

typedef struct				s_list_lights
{
	t_light					*light;
	struct s_list_lights	*next;
}							t_list_lights;

typedef struct				s_scene
{
	double					brightness;
	int						(*effects[14])();
	SDL_Color				dt_col1;
	SDL_Color				dt_col2;
	t_camera				cam;
	t_list_lights			*lights;
	t_list_objs				*objects;
	SDL_Texture				*background;
}							t_scene;

typedef struct				s_thread_data
{
	SDL_Thread				*thread;
	t_scene					scn;
	int						n_thread;
	int						y_begin;
	int						y_end;
}							t_thread_data;

typedef struct				s_blur
{
	SDL_Color				tl1;
	SDL_Color				tr1;
	SDL_Color				bl1;
	SDL_Color				br1;
	SDL_Color				tl2;
	SDL_Color				tr2;
	SDL_Color				bl2;
	SDL_Color				br2;
	SDL_Color				curr;
}							t_blur;

typedef struct				s_duotone
{
	SDL_Color				c1;
	SDL_Color				c2;
}							t_duotone;

typedef struct				s_perlin
{
	SDL_Surface				*perlin;
	int						r;
	int						tmp[512];
	unsigned char			size;
}							t_perlin;

typedef struct				s_screenshot
{
	SDL_Renderer			*renderer;
	SDL_Surface				*surface;
	char					*name;
	SDL_Rect				winsize;
}							t_screenshot;

typedef struct				s_loadingbar
{
	SDL_Texture				*loadingtexture;
	int						val;
	int						old;
}							t_loadingbar;

#endif
