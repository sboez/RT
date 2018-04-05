/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 13:44:18 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/20 19:11:16 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EFFECTS_H
# define EFFECTS_H
# include "structures.h"

/*
** parsing effects
*/
char		*parsing_anaglyph(char *data, t_scene *scn, int *i);
char		*parsing_blur(char *data, t_scene *scn, int *i);
char		*parsing_bwnoise(char *data, t_scene *scn, int *i);
char		*parsing_cartoon(char *data, t_scene *scn, int *i);
char		*parsing_duotone(char *data, t_scene *scn, int *i);
char		*parsing_gray(char *data, t_scene *scn, int *i);
char		*parsing_laplacian(char *data, t_scene *scn, int *i);
char		*parsing_lofi(char *data, t_scene *scn, int *i);
char		*parsing_motionblur(char *data, t_scene *scn, int *i);
char		*parsing_negative(char *data, t_scene *scn, int *i);
char		*parsing_noise(char *data, t_scene *scn, int *i);
char		*parsing_pop(char *data, t_scene *scn, int *i);
char		*parsing_prewitt(char *data, t_scene *scn, int *i);
char		*parsing_sepia(char *data, t_scene *scn, int *i);

/*
** effect_blur.c
*/
SDL_Color	get_pixel_colors(SDL_Surface *screen, int x, int y);
SDL_Color	pixelaccess(SDL_Surface *s, int x, int y, SDL_Color curr);
SDL_Color	blur_color_picker(t_blur c);
void		apply_blur(SDL_Surface *screen, int x, int y);
int			blur(void);

/*
** effect_gray.c
*/
int			gray(void);
void		apply_gray(SDL_Surface *screen, int x, int y);

/*
** effect_sepia.c
*/
int			sepia(void);
void		apply_sepia(SDL_Surface *screen, int x, int y);

/*
** effect_lofi.c
*/
int			lofi(void);
void		apply_lofi(SDL_Surface *screen, int x, int y);

/*
** effect_anaglyph.c
*/
int			anaglyph(void);
void		apply_anaglyph(SDL_Surface *screen, int x, int y);

/*
** effect_negative.c
*/
int			negative(void);
void		apply_negative(SDL_Surface *screen, int x, int y);

/*
** effect_pop.c
*/
int			pop(void);
void		apply_pop(SDL_Surface *screen, int x, int y);

/*
** effect_noise.c
*/
int			noise(void);
void		apply_noise(SDL_Surface *screen, int x, int y);

/*
** effect_laplacian.c
*/
t_blur		surrounding_pixels(SDL_Surface *screen, int x, int y);
int			laplacian(void);
void		apply_laplacian(SDL_Surface *screen, int x, int y);

/*
** effect_prewitt.c
*/
int			prewitt(void);
void		apply_prewitt(SDL_Surface *screen, int x, int y);

/*
** effect_bwnoise.c
*/
int			bwnoise(void);
void		apply_bwnoise(SDL_Surface *screen, int x, int y);

/*
** effect_duotone.c
*/
int			duotone(SDL_Color col1, SDL_Color col2);
void		apply_duotone(SDL_Surface *screen, int x, int y, t_duotone t);

/*
** effect_cartoon.c
*/
int			cartoon(void);
void		apply_cartoon(SDL_Surface *screen, SDL_Surface *cartoon, int x,
						int y);

/*
** effect_motionblur.c
*/
int			motionblur(void);
void		apply_motionblur(SDL_Surface *screen, int x, int y);

/*
** perlin.c
*/
void		put_pixel32(SDL_Surface *surface, int x, int y, Uint32 colors);
int			set_color(unsigned char a, unsigned char r, unsigned char v,
						unsigned char b);
int			rand_between(int min, int max);
int			randbet255(int r, int c, int val);
void		perlinmaker(t_perlin *p, int x, int y);
void		perlin_pinpin(int x, int y);

#endif
