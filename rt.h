/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 16:51:43 by qmuntada          #+#    #+#             */
/*   Updated: 2015/05/04 17:58:05 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "minilibx_macos/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"

# define ESC 53
# define S 1
# define W 13
# define A 0
# define D 2
# define FOV 2.0
# define GAMMA 1.0
# define REF_MAX 6

typedef struct			s_obj
{
	int					type;
	t_vec3				pos;
	t_vec3				rot;
	t_vec3				color;
	double				size;
	double				power;
	double				ref;
	struct s_obj		*next;
}						t_obj;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	int					screen_height;
	int					screen_width;
	t_vec3				cam_pos;
	t_vec3				cam_dir;
	t_vec3				ro;
	t_vec3				rd;
	t_vec3				col;
	t_obj				*obj;
	char				*screen_name;
	double				ln;
	double				tmin;
	int					iter;
}						t_env;

int						expose_hook(t_env *e);
int						key_press(int keycode, t_env *e);
int						key_release(int keycode, t_env *e);
void					parser(t_env *e, int ac, char **av);
void					file_reader(t_env *e, t_list *list);
void					get_name(t_env *e, char *info);
void					get_camera(t_env *e, char *info, int type);
void					get_render(t_env *e, char *info);
void					get_color(t_obj *obj, char *info);
void					get_double(t_obj *obj, char *info, int type);
void					get_objvec(t_vec3 *vec, char *info);
void					objinit(t_obj *obj);
t_obj					*objnew(t_obj *obj);
void					objpushback(t_env *e, t_obj *obj);
void					init_env_preparsing(t_env *e);
void					init_env_postparsing(t_env *e);
void					pixel_put(t_env *e, int x, int y);
void					display(t_env *e);
void					vecnorm(t_vec3 *vec);
double					vecdot(t_vec3 *a, t_vec3 *b);
t_vec3					vecsub(t_vec3 *a, t_vec3 *b);
double					veclength(t_vec3 *vec);
t_vec3					veccross(t_vec3 *a, t_vec3 *b);
t_vec3					vecadd(t_vec3 *a, t_vec3 *b);
t_vec3					vecdiv(t_vec3 *a, t_vec3 *b);
t_vec3					vecprod(t_vec3 *a, t_vec3 *b);
t_vec3					vecopx(t_vec3 *a, double x);
t_vec3					vecreflect(t_vec3 *i, t_vec3 *n);
t_vec3					vecopplus(t_vec3 *a, double x);
t_vec3					vecopdiv(t_vec3 *a, double x);
void					vecclamp(t_vec3 *vec, double a, double b);
void					get_lighting(t_env *e, t_vec3 *col, t_vec3 *pos, \
							t_vec3 *nor);
t_obj					*inter_object(t_env *e, t_vec3 *ro, t_vec3 *rd, \
							double *dmin);
double					inter_shadows(t_env *e, t_vec3 *pos, t_vec3 *lpos);
double					vecdistance(t_vec3 *a, t_vec3 *b);
t_vec3					lambert(t_obj *obj, t_vec3 *nor, t_vec3 *pos);
double					phong(t_obj *obj, t_vec3 *nor, t_vec3 *rd, t_vec3 *pos);
t_vec3					setnor(t_obj *obj, t_vec3 *pos);

#endif
