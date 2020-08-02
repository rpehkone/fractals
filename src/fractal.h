/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/01 14:50:23 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "mlx_io.h"
# include <pthread.h>

#include <stdio.h>
//poista taa struct?
typedef struct	s_float_xy {
	float		x;
	float		y;
}				t_float_xy;

typedef struct	s_args {
	t_float_xy	pos;
	float		zoom;
	int			max_iter;
	int			fractal_id;
	int			**iteration;
	int			threads_ready;
	int			sync_threads;
	int			which;
	int			color;
}				t_args;

void			mandelbrot(t_args *args, int start, int stop);
void			julia(t_args *args, int start, int stop);
void			burningship(t_args *args, int start, int stop);
t_args				*init_fractal(int i);
void			color_settings(t_args *args);
int			select_color(int color, int max, int other, int iteration);
#endif
