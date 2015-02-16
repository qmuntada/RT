/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 19:30:55 by qmuntada          #+#    #+#             */
/*   Updated: 2015/02/06 18:47:10 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_cam(t_env *e, double x, double y)
{
	double	u;
	double	v;
	t_vec	ww;
	t_vec	uu;
	t_vec	vv;

	u = (e->screen_width - x * 2.0) / e->screen_height;
	v = (e->screen_height - y * 2.0) / e->screen_height;
	ww = vecsub(&e->cam_dir, &e->cam_pos);
	vecnorm(&ww);
	uu = veccross(&ww, &(t_vec){0.0, 1.0, 0.0});
	vecnorm(&uu);
	vv = veccross(&uu, &ww);
	e->rd = (t_vec){u * uu.x + v * vv.x + FOV * ww.x, u * uu.y + v * \
		vv.y + FOV * ww.y, u * uu.z + v * vv.z + FOV * ww.z};
	e->ro = e->cam_pos;
}

t_vec	object_color(t_env *e, t_vec *ro, t_vec *rd)
{
	t_vec	pos;
	t_vec	col2;
	t_vec	nor;
	t_vec	nrd;
	t_vec	col;
	t_obj	*objs;

	e->tmin = 10000.0;
	objs = inter_object(e, ro, rd, &e->tmin);
	col = (t_vec){0.0, 0.0, 0.0};
	if (e->tmin > 0.0001 && objs)
	{
		col = (t_vec){objs->color.x, objs->color.y, objs->color.z};
		if (e->tmin < 10000.0)
		{
			pos = (t_vec){ro->x + e->tmin * rd->x, ro->y + e->tmin * \
				rd->y, ro->z + e->tmin * rd->z};
			nor = setnor(objs, &pos);
			get_lighting(e, &col, &pos, &nor);
		}
		if (objs->ref < 1.0 && e->iter < REF_MAX)
		{
			e->iter += 1;
			nrd = *rd;
			vecnorm(&nrd);
			nrd = vecreflect(&nrd, &nor);
			vecnorm(&nrd);
			nor = vecopx(&nor, 0.001);
			pos = vecadd(&pos, &nor);
			col = vecopx(&col, objs->ref);
			col2 = object_color(e, &pos, &nrd);
			col2 = vecopx(&col2, 1.0 - objs->ref);
			col = vecadd(&col, &col2);
			col = vecopdiv(&col, 2.0);
			e->ref += (1 - objs->ref);
		}
	}
	return (col);
}

t_vec	ray_tracing(t_env *e, double x, double y)
{
	t_vec	col;

	set_cam(e, x, y);
	e->iter = 0;
	e->ref = 1.0;
	col = object_color(e, &e->ro, &e->rd);
	return (col);
}

void	display(t_env *e)
{
	int		x;
	int		y;
	t_vec	col2;

	y = -1;
	while (++y < e->screen_height)
	{
		x = -1;
		while (++x < e->screen_width)
		{
			e->col = ray_tracing(e, x, y);
			col2 = ray_tracing(e, x + 0.5, y);
			e->col = vecadd(&e->col, &col2);
			col2 = ray_tracing(e, x, y + 0.5);
			e->col = vecadd(&e->col, &col2);
			col2 = ray_tracing(e, x + 0.5, y + 0.5);
			e->col = vecadd(&e->col, &col2);
			e->col = vecopdiv(&e->col, 4.0);
			e->col.x = pow(e->col.x, GAMMA);
			e->col.y = pow(e->col.y, GAMMA);
			e->col.z = pow(e->col.z, GAMMA);
			vecclamp(&e->col, 0.0, 1.0);
			pixel_put(e, x, y);
		}
	}
}
