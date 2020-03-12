/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 20:12:26 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "fdf.h"
# include <pthread.h>

#include <stdio.h>

typedef struct	s_float_xy {
	float		x;
	float		y;
}				t_float_xy;

typedef struct	s_args {
	t_float_xy	pos;
	float		zoom;
	int			max_iter;
}				t_args;

void			mandelbrot_loop(t_float_xy pos, float zoom,
														int max_iter, int i);
void			julia_loop(t_float_xy pos, float zoom, int max_iter, int i);
void			burningship_loop(t_float_xy pos, float zoom,
														int max_iter, int i);

#endif
